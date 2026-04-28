#include "eltex_shell.h"

void wait_all_children(pid_t *executable_pid, int **exec_err, int n_children) {
  pid_t *pid_ptr;
  int **error_pipe_ptr;
  for (pid_ptr = executable_pid, error_pipe_ptr = exec_err;
       pid_ptr - executable_pid < n_children; pid_ptr++, error_pipe_ptr++) {
    read_exec_err(*error_pipe_ptr);
    wait4child(*pid_ptr);
  }
}
