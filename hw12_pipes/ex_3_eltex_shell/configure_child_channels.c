#include "eltex_shell.h"

int configure_child_channels(int *exec_pipe_in, int *exec_pipe_out) {
  int err = 0;

  // конфигурируем каналы межпроцессного взаимодействия
  if (NULL != exec_pipe_in) {
    errno = 0;
    if (-1 == close(exec_pipe_in[1])) {
      perror("close");
      err = -1;
    }
    errno = 0;
    if (0 == err && -1 == dup2(exec_pipe_in[0], 0)) {
      perror("dup2");
      err = -1;
    }
  }

  if (0 == err && NULL != exec_pipe_out) {
    errno = 0;
    if (-1 == close(exec_pipe_out[0])) {
      perror("close");
      err = -1;
    }
    errno = 0;
    if (0 == err && -1 == dup2(exec_pipe_out[1], 1)) {
      perror("dup2");
      err = -1;
    }
  }

  return err;
}
