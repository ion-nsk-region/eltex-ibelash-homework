#include "client.h"

int spawn_input_thread(struct chat_msg *msg, sem_t *input_updated,
                       sem_t *input_read, WINDOW *input_window,
                       pthread_t *input_tid) {
  int err = 0;

  struct input_args *input_args = malloc(sizeof(struct input_args));
  input_args->msg = msg;
  input_args->input_updated = input_updated;
  input_args->input_read = input_read;
  input_args->input_window = input_window;

  err = pthread_create(input_tid, NULL, input, input_args);
  if (0 != err) {
    perror("input pthread_create");
  }

  return err;
}
