#include "client.h"

int spawn_threads(pthread_mutex_t *refresh_lock, pthread_cond_t *refresh_cond,
                  struct chat_msg **msg, int *ch, pthread_t *reader_tid,
                  pthread_t *input_tid) {
  int err = 0;

  // запускаем поток для чтения сообщений от сервера
  struct reader_args *reader_args = malloc(sizeof(struct reader_args));
  reader_args->refresh_lock = refresh_lock;
  reader_args->refresh_cond = refresh_cond;
  reader_args->msg = msg;

  if (0 != (err = pthread_create(reader_tid, NULL, reader, reader_args))) {
    perror("reader pthread_create");
  } else {
    // printf("DEBUG запущен поток с tid %ld\n", *reader_tid);
  }

  // запускаем поток для обработки пользовательского ввода и отправки сообщений
  if (0 == err) {
    struct input_args *input_args = malloc(sizeof(struct input_args));
    input_args->refresh_lock = refresh_lock;
    input_args->refresh_cond = refresh_cond;
    input_args->ch = ch;
    //    input_args->win = NULL;

    if (0 != (err = pthread_create(input_tid, NULL, input, input_args))) {
      perror("input pthread_create");
    }
  }

  return err;
}
