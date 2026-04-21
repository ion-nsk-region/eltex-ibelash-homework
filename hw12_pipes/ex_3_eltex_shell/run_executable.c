#include "eltex_shell.h"

int run_executable(char **arguments, int *exec_err) {
  int err = 0;
  // закрываем канал ошибок на чтение, только пишем
  errno = 0;
  if (-1 == close(exec_err[0])) {
    perror("close");
    err -= 1;
  }

  // запускаем наш исполняемый файл
  errno = 0;
  if (-1 == execvp(arguments[0], arguments)) {
    int exec_error = errno;
    // perror("execvp");
    // В случае ошибки exec, возвращаем её через канал
    errno = 0;
    if (-1 == write(exec_err[1], &exec_error, sizeof(int))) {
      perror("write");
    }
    _exit(0);
  }

  return err;
}
