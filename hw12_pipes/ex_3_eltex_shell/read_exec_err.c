#include "eltex_shell.h"

int read_exec_err(int *error_pipe) {
  int err = 0;
  if (0 != close_pipe_end(error_pipe[1])) {
    fprintf(stderr,
            "Ошибка: Родителю не удалось закрыть на запись канал ошибок "
            "%d.\n",
            error_pipe[1]);
  }

  // Читаем и обрабатываем ошибку
  ssize_t count;
  int exec_error;
  while (-1 == (count = read(error_pipe[0], &exec_error, sizeof(errno)))) {
    if (EAGAIN != errno && EINTR != errno) break;
  }
  if (count) {
    fprintf(stderr, "Ошибка: не удалось запустить последнюю команду: %s\n",
            strerror(exec_error));
  }

  // закрываем канал окончательно
  err = close_pipe_end(error_pipe[0]);

  return err;
}
