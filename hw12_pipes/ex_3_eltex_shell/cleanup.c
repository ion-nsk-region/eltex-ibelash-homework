#include "eltex_shell.h"

void cleanup(char ****arguments, int ***exec_err, int ***exec_pipe,
             int n_pipes) {
  if (NULL != arguments) {
    for (char ***p = *arguments; p - *arguments <= n_pipes; p++) {
      free(*p);
    }
    free(*arguments);
    *arguments = NULL;
  }
  if (NULL != *exec_err) {
    for (int **p = *exec_err; p - *exec_err <= n_pipes; p++) {
      if (NULL != *p) {
        free(*p);
      }
    }
    free(*exec_err);
    *exec_err = NULL;
  }
  if (NULL != *exec_pipe) {
    for (int **p = *exec_pipe; p - *exec_pipe < n_pipes; p++) {
      if (NULL != *p) {
        free(*p);
      }
    }
    free(*exec_pipe);
    *exec_pipe = NULL;
  }
}
