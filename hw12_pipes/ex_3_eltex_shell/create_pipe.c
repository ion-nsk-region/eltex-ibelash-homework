#include "eltex_shell.h"

int create_pipe(int *exec_pipe) {
  int err = 0;
  errno = 0;
  exec_pipe = (int *)malloc(sizeof(int) * 2);
  if (NULL == exec_pipe) {
    perror("malloc");
    err = -1;
  }
  errno = 0;
  if (0 == err && -1 == pipe(exec_pipe)) {
    perror("pipe");
    err = -2;
  }
  errno = 0;
  if (0 == err && -1 == fcntl(exec_pipe[1], F_SETFD,
                              fcntl(exec_pipe[1], F_GETFD) | FD_CLOEXEC)) {
    perror("fcntl");
    err = -3;
  }
  return err;
}
