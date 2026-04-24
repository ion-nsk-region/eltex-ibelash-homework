#include "eltex_shell.h"

int close_pipe_end(int pipe_end) {
  int err;

  errno = 0;
  if (-1 == (err = close(pipe_end))) {
    perror("close");
  }

  return err;
}
