#include "client.h"

void *input(void *arg) {
  int buf_char = 0;
  struct input_args args = *(struct input_args *)arg;
  free(arg);

  while (EOF != (buf_char = getchar())) {
    //  while (EOF != (buf_char = wgetch(ui.msg_input))) { // TODO перейти на
    //  wgetch, чтобы забирать управляющие клавиши, включая KEY_RESIZE.
    pthread_mutex_lock(args.refresh_lock);
    *(args.ch) = buf_char;
    pthread_cond_signal(args.refresh_cond);
    pthread_mutex_unlock(args.refresh_lock);
  }

  return (void *)0;
}
