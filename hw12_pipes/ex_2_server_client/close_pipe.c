#include "mypipe2.h"

int close_pipe(int pipe_fd) {
  int err;

  errno = 0;
  if (-1 == (err = close(pipe_fd))) {
    perror("close");
  }

  return err;
}
