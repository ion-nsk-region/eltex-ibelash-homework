#include "eltex_shell.h"

int create_pipes(int n_pipes, int **exec_err, int **exec_pipe) {
  int err = 0;

  errno = 0;
  exec_err = (int **)malloc((n_pipes + 1) * sizeof(int *));
  if (NULL == exec_err) {
    perror("malloc");
    // fprintf(stderr, "Ошибка: не удалось выделить память для указателей на
    // каналы ошибок.\n");
    err = -1;
  }
  if (0 == err && 0 < n_pipes) {
    errno = 0;
    exec_pipe = (int **)malloc(n_pipes * sizeof(int *));
    if (NULL == exec_pipe) {
      perror("malloc");
      // fprintf(stderr, "Ошибка: не удалось выделить память для указателей на
      // каналы межпроцессного взаимодействия.\n");
      err = -1;
    }
  } else {
    exec_pipe = NULL;
  }

  // делаем канал, чтобы возвращать код ошибки от exec
  // позаимствовано отсюда:
  // https://acm.bsu.by/wiki/Unix2018/%D0%A2%D0%B5%D1%85%D0%BD%D0%B8%D0%BA%D0%B0_fork_%E2%80%94_exec#.D0.A0.D0.B5.D1.88.D0.B5.D0.BD.D0.B8.D0.B5_.D0.BF.D1.80.D0.BE.D0.B1.D0.BB.D0.B5.D0.BC.D1.8B_.D0.BE.D1.82.D0.BB.D0.BE.D0.B2.D0.B0_.D0.BE.D1.88.D0.B8.D0.B1.D0.BA.D0.B8_exec
  if (0 == err && 0 > create_pipe(*exec_err)) {
    fprintf(stderr,
            "Ошибка: не удалось создать канал для чтения ошибок запуска "
            "дочерних процессов. См. подробности в stderr.\n");
    err = -1;
  }

  if (0 == err) {
    for (int i = 0; i < n_pipes; i++) {
      if (0 == err && 0 > create_pipe(*(exec_err + i + 1))) {
        fprintf(stderr,
                "Ошибка: не удалось создать канал для чтения ошибок запуска "
                "дочерних процессов. См. подробности в stderr.\n");
        err = -1;
      }
      if (0 == err && 0 > create_pipe(*(exec_pipe + i))) {
        fprintf(stderr,
                "Ошибка: не удалось создать канал для межпроцессного "
                "взаимодействия. См. подробности в stderr.\n");
        err = -1;
      }
    }
  }

  return err;
}
