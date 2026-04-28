#include "eltex_shell.h"

int wait4child(pid_t executable_pid) {
  int err = 0;

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
