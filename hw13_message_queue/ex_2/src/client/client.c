#include "client.h"

int main(void) {
  int err = 0;
  pthread_mutex_t refresh_lock, msg_processing_lock, ch_processing_lock;
  pthread_cond_t refresh_cond, msg_processing_cond, ch_processing_cond;
  pthread_t reader_tid = pthread_self(), input_tid = pthread_self();
  struct chat_msg *msg = NULL;
  int ch = 0, ch_is_processing = 0, msg_is_processing = 0;
  struct ui ui = {NULL, NULL, NULL};
  struct user users[MAX_CHAT_USERS] = {};
  int n_users = 0;

  char *server_mq_name = SERVER_MQ_NAME;
  int server_mq_id = -1;
  // подключаемся к очереди сервера
  err = connect2mq(server_mq_name, &server_mq_id);
  if (ETIME == err) {
    printf("Ошибка: время ожидания сервера истекло.\n");
  } else if (0 != err) {
    printf("Ошибка connect2mq: %d\nСм. подробности в stderr.\n", err);
  }

  if (0 == err) err = nickname_prompt(server_mq_id);
  if (0 == err) {
    pthread_mutex_init(&msg_processing_lock, NULL);
    pthread_cond_init(&msg_processing_cond, NULL);
    pthread_mutex_init(&ch_processing_lock, NULL);
    pthread_cond_init(&ch_processing_cond, NULL);
    pthread_mutex_init(&refresh_lock, NULL);
    pthread_cond_init(&refresh_cond, NULL);

    pthread_mutex_lock(
        &refresh_lock);  // блокируем изменение переменных в потоках
    err = spawn_threads(&refresh_lock, &refresh_cond, &msg, &msg_is_processing,
                        &msg_processing_lock, &msg_processing_cond, &ch,
                        &ch_is_processing, &ch_processing_lock,
                        &ch_processing_cond, ui.msg_input, &reader_tid,
                        &input_tid);
  }
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

  pthread_mutex_unlock(&refresh_lock);

  destroy_windows(ui);
  client_cleanup(reader_tid, input_tid, &refresh_lock, &refresh_cond,
                 &msg_processing_lock, &msg_processing_cond,
                 &ch_processing_lock, &ch_processing_cond, users, n_users);

  if (NULL != msg && QUIT == msg->cmd && getpid() != msg->sender) {
    printf("\nСервер завершил свою работу. Выходим.\n");
  } else {
    // пытаемся отправить сообщение серверу, чтобы он убрал нас из списка
    if (-1 != server_mq_id) {
      struct chat_msg quit_msg = {getpid(), QUIT, NULL};
      if (0 != send_mq_msg(server_mq_id, 1, quit_msg)) {
        fprintf(stderr,
                "Ошибка: не удалось отправить сообщение о выходе.\n"
                "Требуется перезагрузка сервера.\n");
      }
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
