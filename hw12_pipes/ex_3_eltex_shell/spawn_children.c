#include "eltex_shell.h"

int spawn_children(char **all_args, int n_pipes, int **exec_err,
                   int **exec_pipe, int n_words) {
  int err = 0, n_children = n_pipes + 1;
  char **arguments;

  errno = 0;
  pid_t *executable_pid = (pid_t *)malloc(sizeof(pid_t) * (n_children));
  if (NULL == executable_pid) {
    perror("malloc");
    err = -1;
  }

  errno = 0;
  arguments = (char **)malloc((n_words + 1) * sizeof(char *));
  if (NULL == arguments) {
    perror("malloc");
    err = -1;
  }

  if (0 == err) {
    int *exec_pipe_out, *exec_pipe_in;
    if (0 < n_pipes && NULL != exec_pipe) exec_pipe_out = *exec_pipe;
    for (int i = 0; i < n_children; i++) {
      parse_single_command(*all_args, arguments);
      int *error_pipe = *exec_err;
      if (0 < i && i <= n_pipes && NULL != exec_pipe) {
        exec_pipe_in = *exec_pipe;
      }
      if (i < n_pipes) {
        all_args++;
        exec_err++;
        if (NULL != exec_pipe) {
          exec_pipe++;
          exec_pipe_out = *exec_pipe;
        }
      }

      errno = 0;
      *executable_pid = fork();
      if (-1 == *executable_pid) {
        perror("fork");
        err -= 1;
      } else if (0 == *executable_pid) {
        // Дочерний процесс:
        // - конфигурируем каналы
        if (0 == err && NULL != exec_pipe) {
          err = configure_child_channels(exec_pipe_in, exec_pipe_out);
        }
        // - запускаем наш исполняемый файл
        if (0 == err) {
          err = run_executable(arguments, error_pipe);
        }
      }
      executable_pid++;
    }
  }

  /*
  // TODO ждём все дочерние процессы
  if (0 == err && 0 < *executable_pid) {
    err = wait_and_handle_errors(*executable_pid, error_pipe);
  }
  */

  free(executable_pid);

  return err;
}
