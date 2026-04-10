#include "ex_1.h"

int wait4child(pid_t child_pid) {
  int status;
  errno = 0;
  if (-1 == waitpid(child_pid, &status, 0)) {
    perror("waitpid");
    status = -1;
  } else if (WIFEXITED(status) && 0 != status) {
    fprintf(stderr,
            "Предупреждение: Дочерний процесс вернул ненулевой статус: %d.\n",
            WEXITSTATUS(status));
  }

  return status;
}
