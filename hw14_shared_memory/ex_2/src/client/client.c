#include "client.h"

int main(void) {
  int err = 0, is_running = 1;
  struct user *users = NULL;
  struct chat_history *history = NULL;
  struct chat_msg *msg = NULL;
  sem_t *data_updated, *count_reads, *next_turn, *input_updated, *input_read;
  struct ui ui = {NULL, NULL, NULL};
  pthread_t input_tid = pthread_self();

  err = init_client(&msg, &input_updated, &input_read, &users, &history, &data_updated, &count_reads, &next_turn, &ui);
  if (0 == err) {
	  err = spawn_input_thread(&msg, &input_updated, &input_read, &ui, &is_running, &input_tid);
  }
  if (0 == err) err = run(users, history, data_updated, count_reads, next_turn, &ui);

  // ======================

  if (0 == err) err = nickname_prompt(server_mq_id);
  if (0 == err) err = initialize_terminal();
  if (0 == err) err = create_windows(&ui);
  if (0 == err) {
    handle_resize(ui);
    print_help(ui);
    wmove(ui.msg_input, 1, 0);  // устанавливаем курсор в начало поля
    refresh_windows(ui);

    int is_running = 1;
    char *input_buf = malloc(get_max_msg_size() - sizeof(struct chat_msg));
    if (NULL == input_buf) {
      perror("malloc");
      err = -1;
    }
    size_t input_buf_length = 0;
    if (0 != err) is_running = 0;

    while (is_running) {
      // ждём сигналов от потоков и обрабатываем условия выхода

      // Рекомендуется оборачивать pthread_cond_wait в цикл, чтобы
      // защититься от ложных пробуждений, которые может инициировать
      // операционная система, а не наши потоки.
      while (0 == ch && NULL == msg) {
        pthread_cond_wait(&refresh_cond, &refresh_lock);
      }
      /*
            fprintf(stderr, "DEBUG обрабатываем: ch = %d, ", ch);
            if (NULL != msg) {
              const char *commands[] = {"NO_COMMAND", "JOIN",    "QUIT",
                                        "LIST",       "HISTORY", "MSG"};
              fprintf(stderr, "msg от %d, тип %s\n", msg->sender,
         commands[msg->cmd]); if (NULL != msg->content) { fprintf(stderr,
         "содержимое: %s.\n", msg->content); } else { fprintf(stderr,
         "содержимое = NULL.\n");
              }
            } else {
              fprintf(stderr, "msg = NULL.\n");
            }
      */

      if (27 == ch || EOF == ch || (NULL != msg && QUIT == msg->cmd))
        is_running = 0;

      if (is_running && NULL != msg && NO_COMMAND != msg->cmd) {
        pthread_mutex_lock(&msg_processing_lock);
        handle_msg(msg, ui, users, &n_users);
        if (NULL != msg->content) free(msg->content);
        free(msg);
        msg = NULL;
        msg_is_processing = 0;
        pthread_cond_signal(&msg_processing_cond);
        pthread_mutex_unlock(&msg_processing_lock);
      }

      if (is_running && 0 != ch) {
        pthread_mutex_lock(&ch_processing_lock);
        handle_input(ui, server_mq_id, ch, input_buf, &input_buf_length);
        ch = 0;
        ch_is_processing = 0;
        pthread_cond_signal(&ch_processing_cond);
        pthread_mutex_unlock(&ch_processing_lock);
      }

      refresh_windows(ui);
    }  // while
    if (NULL != input_buf) free(input_buf);
  }


  // ======================
  destroy_windows(ui);
  client_cleanup(reader_tid, input_tid, &refresh_lock, &refresh_cond,
                 &msg_processing_lock, &msg_processing_cond,
                 &ch_processing_lock, &ch_processing_cond, users, n_users);

  if (NULL != msg && QUIT == msg->cmd && getpid() != msg->sender) {
    printf("\nСервер завершил свою работу. Выходим.\n");
  } else {
    // пытаемся отправить сообщение серверу, чтобы он убрал нас из списка
      struct chat_msg quit_msg = {getpid(), QUIT, NULL};
      if (0 != send_mq_msg(server_mq_id, 1, quit_msg)) {
        fprintf(stderr,
                "Ошибка: не удалось отправить сообщение о выходе.\n"
                "Требуется перезагрузка сервера.\n");
      }
    if (NULL != msg && QUIT == msg->cmd && getpid() == msg->sender) {
      printf("\nВ дочернем потоке возникла ошибка. Выходим.\n");
    } else if (27 == ch) {
      printf("\nНажали Esc. Выходим.\n");
    } else {
      printf("\nПриключилась какая-то оказия. Выходим.\n");
    }
  }

  if (NULL != msg) {
    if (NULL != msg->content) free(msg->content);
    free(msg);
  }

  return err;
}
