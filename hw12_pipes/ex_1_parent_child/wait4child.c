#include "ex_1.h"

int wait4child(pid_t child_pid) {
  int status;
  waitpid(child_pid, &status, 0);

  if (WIFEXITED(status) && 0 != status) {
    fprintf(stderr,
            "Предупреждение: Дочерний процесс вернул ненулевой статус: %d.\n",
            WEXITSTATUS(status));
  }

  return status;
}
