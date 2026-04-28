#include "eltex_shell.h"

int spawn_children(char ***all_args, int n_pipes, int **exec_err,
                   int **exec_pipe) {
  int err = 0, n_children = n_pipes + 1;
  pid_t *executable_pid;

  errno = 0;
  executable_pid = (pid_t *)malloc(sizeof(pid_t) * (n_children));
  if (NULL == executable_pid) {
    perror("malloc");
    err = -1;
  }

  if (0 == err) {
    char ***arg_ptr;
    int **exec_pipe_ptr, **error_pipe_ptr;
    pid_t *pid_ptr;
    for (pid_ptr = executable_pid, error_pipe_ptr = exec_err,
        exec_pipe_ptr = exec_pipe, arg_ptr = all_args;
         pid_ptr - executable_pid < n_children;
         pid_ptr++, error_pipe_ptr++, arg_ptr++) {
      int *exec_pipe_out = NULL, *exec_pipe_in = NULL;
      if (NULL != exec_pipe) {
        if (0 < pid_ptr - executable_pid) {
          exec_pipe_in = *exec_pipe_ptr;
          exec_pipe_ptr++;
        }
        if (pid_ptr - executable_pid < n_pipes) {
          exec_pipe_out = *exec_pipe_ptr;
        }
      }

      err = spawn_single_child(arg_ptr, exec_pipe_in, exec_pipe_out,
                               error_pipe_ptr, pid_ptr);
    }  // for
  }

  // ждём все дочерние процессы
  if (0 == err && 0 < *executable_pid) {
    wait_all_children(executable_pid, exec_err, n_children);
  }

  // освобождаем память
  if (0 != *executable_pid) {
    free(executable_pid);
  }

  return err;
}
