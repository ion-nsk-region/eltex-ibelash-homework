#include "eltex_shell.h"

int wait_and_handle_errors(pid_t executable_pid, int *exec_err) {
  int err = 0;
  // Закрываем канал на запись, только читаем
  errno = 0;
  if (-1 == close(exec_err[1])) {
    perror("close");
    err -= 1;
  }
  // Читаем и обрабатываем ошибку
  ssize_t count;
  int exec_error;
  while (-1 == (count = read(exec_err[0], &exec_error, sizeof(errno)))) {
    if (EAGAIN != errno && EINTR != errno) break;
  }
  if (count) {
    fprintf(stderr, "Ошибка: не удалось запустить команду: %s\n",
            strerror(exec_error));
  }

  // закрываем канал окончательно
  if (-1 == close(exec_err[0])) {
    perror("close");
    err -= 1;
  }

  // Ждём выхода из дочернего процесса
  int status;
  waitpid(executable_pid, &status, 0);
  if (WIFEXITED(status) && 0 != status) {
    fprintf(stderr, "Предупреждение: Команда вернула ненулевой статус: %d\n",
            WEXITSTATUS(status));
  }

  return err;
}
