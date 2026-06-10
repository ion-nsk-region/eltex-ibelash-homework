#include "client.h"

void *input(void *arg) {
  int buf_char = 0;
  struct input_args args = *(struct input_args *)arg;
  free(arg);

  pthread_mutex_lock(args.processing_lock);

  while (EOF != (buf_char = getchar())) {
    // while (EOF != (buf_char = wgetch(args.input_window))) {  // TODO перейти
    // на
    //  wgetch, чтобы забирать управляющие клавиши, включая KEY_RESIZE.
    pthread_mutex_lock(args.refresh_lock);
    *(args.ch) = buf_char;
    *(args.is_processing) = 1;
    pthread_cond_signal(args.refresh_cond);
    pthread_mutex_unlock(args.refresh_lock);

    while (*(args.is_processing)) {
      pthread_cond_wait(args.processing_cond, args.processing_lock);
    }
  }

  pthread_mutex_unlock(args.processing_lock);

  return (void *)0;
}
