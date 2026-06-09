#include "client.h"

void *reader(void *arg) {
  int err = 0;
  struct reader_args args = *(struct reader_args *)arg;
  free(arg);

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
      struct chat_msg *reply_from_server;
      if (0 != (err = read_mq_msg(client_mq_id, my_pid, &reply_from_server))) {
        fprintf(stderr, "Ошибка read_mq_msg: %d\n", err);
      }
      if (NULL != reply_from_server) {
        pthread_mutex_lock(args.refresh_lock);
        *(args.msg) = reply_from_server;
        pthread_cond_signal(args.refresh_cond);
        pthread_mutex_unlock(args.refresh_lock);
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

  return (void *)0;
}
