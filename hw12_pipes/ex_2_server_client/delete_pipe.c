#include "mypipe2.h"

int delete_pipe(char *pipe_path) {
  int err = 0;

  errno = 0;
  err = unlink(pipe_path);
  if (-1 == err && ENOENT != errno) {
    perror("unlink");
  } else {
    err = 0;
  }

  return err;
}
