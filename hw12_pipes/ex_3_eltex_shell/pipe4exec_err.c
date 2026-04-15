#include "eltex_shell.h"

int pipe4exec_err(int *exec_err) {
  int err = 0;
  errno = 0;
  if (-1 == pipe(exec_err)) {
    perror("pipe");
    err -= 1;
  }
  errno = 0;
  if (-1 ==
      fcntl(exec_err[1], F_SETFD, fcntl(exec_err[1], F_GETFD) | FD_CLOEXEC)) {
    perror("fcntl");
    err -= 1;
  }
  return err;
}
