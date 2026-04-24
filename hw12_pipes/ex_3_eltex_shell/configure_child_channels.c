#include "eltex_shell.h"

int configure_child_channels(int *exec_pipe_in, int *exec_pipe_out) {
  int err = 0;

  // конфигурируем каналы межпроцессного взаимодействия
  if (NULL != exec_pipe_in) {
    err = close_pipe_end(exec_pipe_in[1]);

    errno = 0;
    if (0 == err && -1 == dup2(exec_pipe_in[0], 0)) {
      perror("dup2");
      err = -1;
    }
    fprintf(stderr, "DEBUG: Настроили канал %d на чтение входных данных.\n",
            exec_pipe_in[0]);
  }

  if (0 == err && NULL != exec_pipe_out) {
    err = close_pipe_end(exec_pipe_out[0]);

    errno = 0;
    if (0 == err && -1 == dup2(exec_pipe_out[1], 1)) {
      perror("dup2");
      err = -1;
    }
    fprintf(stderr, "DEBUG: Настроили канал %d на вывод данных.\n",
            exec_pipe_out[1]);
  }

  return err;
}
