#include "client.h"

void *reader(void *arg) {
  int err = 0;
  struct reader_args *args = (struct reader_args*)arg;
  int client_mq_id = -1;
  pid_t my_pid = getpid();

  err = connect2mq(CLIENT_MQ_NAME, &client_mq_id);
  printf("DEBUG: получен mq_id = %d.\n", client_mq_id);
  if (ETIME == err) {
    printf("Ошибка: время ожидания сервера истекло.\n");
  } else if (0 != err) {
    printf("Ошибка connect2mq: %d\nСм. подробности в stderr.\n", err);
  }

  if (0 == err && -1 < client_mq_id) {
    //    while (*(args->is_running)) {
    while (1) {
      struct chat_msg *reply_from_server;
      if (0 != (err = read_mq_msg(client_mq_id, my_pid, &reply_from_server))) {
        fprintf(stderr, "Ошибка read_mq_msg: %d\n", err);
      }
      if (NULL != reply_from_server) {
        pthread_mutex_lock(args->refresh_lock);
        *(args->msg) = reply_from_server;
        pthread_cond_signal(args->refresh_cond);
        pthread_mutex_unlock(args->refresh_lock);
      }
    }  // while
  } else {
    struct chat_msg *quit = malloc(sizeof(struct chat_msg));
    quit->cmd = QUIT;
        pthread_mutex_lock(args->refresh_lock);
        *(args->msg) = quit;
        pthread_cond_signal(args->refresh_cond);
        pthread_mutex_unlock(args->refresh_lock);
  }

  return (void *)0;
}
