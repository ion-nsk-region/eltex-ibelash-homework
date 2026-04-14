#include "mypipe2.h"

int read_msg_from_pipe(char *pipe_path, int conn_timeout, char *msg) {
  int err = 0, pipe_fd;

  err = wait4server(pipe_path, conn_timeout, &pipe_fd);

  errno = 0;
  if (0 == err) {
    if (-1 == read(pipe_fd, msg, PIPE_BUF)) {
      perror("read");
      err = -1;
    }
  }

  if (0 < pipe_fd) {
    err += close_pipe(pipe_fd);
  }

  return err;
}
