#include "client.h"

int main(void) {
  int err = 0;// , is_running = 1;
  struct user *users = NULL;
  struct chat_history *history = NULL;
  struct chat_msg *msg = NULL;
  sem_t *data_updated = NULL, *count_reads = NULL, *next_turn = NULL, *input_updated = NULL, *input_read = NULL;
  struct ui ui = {NULL, NULL, NULL};
  // pthread_t input_tid = pthread_self();

  err = init_client(&msg, &input_updated, &input_read, &users, &history, &data_updated, &count_reads, &next_turn, &ui);
  //if (0 != err) goto exit;
  /*
  if (0 == err) {
	  err = spawn_input_thread(&msg, &input_updated, &input_read, &ui, &is_running, &input_tid);
  }
  if (0 == err) err = run(users, history, data_updated, count_reads, next_turn, &ui);
*/
  // ======================

  /*
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
      */

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
/*
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

*/
sleep(3);

  // ======================

  // handle_exit();

  // err = close_input_thread(input_tid);

  client_cleanup(&msg, &input_updated, &input_read, &users, &history, &data_updated, &count_reads, &next_turn, &ui);

// exit:
  return err;
}
