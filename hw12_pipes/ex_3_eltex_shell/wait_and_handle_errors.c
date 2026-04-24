#include "eltex_shell.h"

int wait_and_handle_errors(pid_t executable_pid) {
  // int wait_and_handle_errors(pid_t executable_pid, int *exec_err) {
  // int wait_and_handle_errors(void) {
  int err = 0;
  /*
  // Закрываем канал на запись, только читаем
  err = close_pipe_end(exec_err[1]);

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
  err = close_pipe_end(exec_err[0]);
  */

  // Ждём выхода из дочернего процесса
  int status;
  pid_t child_pid = waitpid(executable_pid, &status, 0);
  if (WIFEXITED(status) && 0 != status) {
    fprintf(stderr, "Предупреждение: Процесс %d вернул ненулевой статус: %d\n",
            child_pid, WEXITSTATUS(status));
    err = -1;
  }

  return err;
}
