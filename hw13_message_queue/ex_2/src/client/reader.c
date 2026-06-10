#include "client.h"

void *reader(void *arg) {
  int err = 0;
  struct reader_args args = *(struct reader_args *)arg;
  free(arg);

  pthread_mutex_lock(args.processing_lock);

  int client_mq_id = -1;
  pid_t my_pid = getpid();

  err = connect2mq(CLIENT_MQ_NAME, &client_mq_id);
  if (ETIME == err) {
    fprintf(stderr, "Ошибка: время ожидания сервера истекло.\n");
  } else if (0 != err) {
    fprintf(stderr, "Ошибка connect2mq: %d\nСм. подробности в stderr.\n", err);
  }

  if (0 == err && -1 < client_mq_id) {
    //    while (*(args.is_running)) { // не подходит так как поток блокируется
    //    на чтении и не дойдёт до проверки условия.
    while (1) {
      struct chat_msg *reply_buf = NULL;
      err = read_mq_msg(client_mq_id, my_pid, &reply_buf);
      if (0 != err) {
        fprintf(stderr, "Ошибка read_mq_msg: %d\n", err);
      }
      if (NULL != reply_buf) {
        pthread_mutex_lock(args.refresh_lock);

        struct chat_msg *server_reply = malloc(sizeof(struct chat_msg));
        server_reply->sender = reply_buf->sender;
        server_reply->cmd = reply_buf->cmd;
        if (NULL != reply_buf->content) {
          size_t content_length = strlen(reply_buf->content) + 1;
          server_reply->content = malloc(content_length);
          strncpy(server_reply->content, reply_buf->content, content_length);
        } else {
          server_reply->content = NULL;
        }
        *(args.msg) = server_reply;
        *(args.is_processing) = 1;
        if (NULL != reply_buf->content) free(reply_buf->content);
        free(reply_buf);

        pthread_cond_signal(args.refresh_cond);
        pthread_mutex_unlock(args.refresh_lock);

        // блокируем поток пока main не начнёт обработку сообщения
        while (*(args.is_processing)) {
          pthread_cond_wait(args.processing_cond, args.processing_lock);
        }

      } else {
        fprintf(stderr, "Ошибка read_mq_msg: записан пустой буфер.\n");
      }
    }  // while
  } else {
    // Даём знать основному потоку, что надо выходить.
    struct chat_msg *quit = malloc(sizeof(struct chat_msg));
    quit->sender = getpid();
    quit->cmd = QUIT;
    pthread_mutex_lock(args.refresh_lock);
    *(args.msg) = quit;
    pthread_cond_signal(args.refresh_cond);
    pthread_mutex_unlock(args.refresh_lock);
  }

  pthread_mutex_unlock(args.processing_lock);

  return (void *)0;
}
