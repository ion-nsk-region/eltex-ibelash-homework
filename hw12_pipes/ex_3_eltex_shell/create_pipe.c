#include "eltex_shell.h"

int create_pipe(int **ptr_pipe) {
  int err = 0;
  errno = 0;
  *ptr_pipe = (int *)malloc(sizeof(int) * 2);
  if (NULL == *ptr_pipe) {
    perror("malloc");
    err = -1;
  }
  errno = 0;
  if (0 == err && -1 == pipe(*ptr_pipe)) {
    perror("pipe");
    err = -2;
  }

  // TODO специфично для канала ошибок. Вынести в конфигурацию канала.
  /*
  errno = 0;
  if (0 == err && -1 == fcntl((*ptr_pipe)[1], F_SETFD,
                              fcntl((*ptr_pipe)[1], F_GETFD) | FD_CLOEXEC)) {
    perror("fcntl");
    err = -3;
  }
  */
  return err;
}
