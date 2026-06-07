#include "client.h"

void *input(void *arg) {
  int buf_char = 0;
  struct input_args *args = (struct input_args *)arg;

  while (EOF != (buf_char = getchar())) {
    pthread_mutex_lock(args->refresh_lock);
    *(args->ch) = buf_char;
    pthread_cond_signal(args->refresh_cond);
    pthread_mutex_unlock(args->refresh_lock);
  }

  return (void *)0;
}
