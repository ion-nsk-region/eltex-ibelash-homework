#include "eltex_shell.h"

int create_pipes(int ***ptr_pipes, int n_pipes) {
  int err = 0;

  errno = 0;
  if (0 < n_pipes) {
    *ptr_pipes = (int **)malloc(n_pipes * sizeof(int *));
    if (NULL == *ptr_pipes) {
      perror("malloc");
      err = -1;
    }
  } else {
    *ptr_pipes = NULL;
  }

  if (0 == err) {
    for (int **p = *ptr_pipes; p - *ptr_pipes < n_pipes; p++) {
      if (0 == err && 0 > (err = create_pipe(p))) {
        fprintf(
            stderr,
            "Ошибка: не удалось создать канал. См. подробности в stderr.\n");
      }
    }
  }

  return err;
}
