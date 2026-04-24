#include "eltex_shell.h"

int spawn_children(char **all_args, int n_pipes, int **exec_err,
                   int **exec_pipe, int n_words) {
  int err = 0, n_children = n_pipes + 1;
  char **arguments;
  int **error_pipe;
  pid_t *pid_ptr, *executable_pid;

  errno = 0;
  executable_pid = (pid_t *)malloc(sizeof(pid_t) * (n_children));
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
    for (pid_ptr = executable_pid, error_pipe = exec_err;
         pid_ptr - executable_pid < n_children;
         pid_ptr++, error_pipe++, all_args++) {
      int *exec_pipe_out = NULL, *exec_pipe_in = NULL;
      parse_single_command(*all_args, arguments);
      if (NULL != exec_pipe) {
        if (pid_ptr - executable_pid < n_pipes) {
          exec_pipe_out = *exec_pipe;
        }
        if (0 < pid_ptr - executable_pid) {
          exec_pipe_in = *exec_pipe;
          exec_pipe++;
        }
      }

      errno = 0;
      *pid_ptr = fork();
      if (-1 == *pid_ptr) {
        perror("fork");
        err -= 1;
      } else if (0 == *pid_ptr) {
        // Дочерний процесс:
        // - конфигурируем каналы
        if (0 == err && NULL != exec_pipe) {
          err = configure_child_channels(exec_pipe_in, exec_pipe_out);
        }
        // - запускаем наш исполняемый файл
        if (0 == err) {
          err = run_executable(arguments, *error_pipe);
        } else {
          fprintf(stderr,
                  "Не удалось запустить процесс %s так как не были настроены "
                  "каналы. Код ошибки %d.\n",
                  *arguments, err);
        }
      } else if (0 < *pid_ptr) {
        // Родитель
        // закрываем межпроцессный канал - родитель им пользоваться не будет.
        if (NULL != exec_pipe_in && (0 != close_pipe_end(exec_pipe_in[0]) ||
                                     0 != close_pipe_end(exec_pipe_in[1]))) {
          fprintf(stderr,
                  "Ошибка: Родителю не удалось отсоединиться от канала {%d %d}"
                  "дочерних процессов. См. подробности в stderr.\n",
                  exec_pipe_in[0], exec_pipe_in[1]);
        }
        // закрываем на запись канал ошибок
        if (0 != close_pipe_end((*error_pipe)[1])) {
          fprintf(stderr,
                  "Ошибка: Родителю не удалось закрыть на запись канал ошибок "
                  "%d.\n",
                  (*error_pipe)[1]);
        }
      }
    }  // for
  }

  // TODO ждём все дочерние процессы
  if (0 == err && 0 < *executable_pid) {
    for (pid_ptr = executable_pid, error_pipe = exec_err;
         pid_ptr - executable_pid < n_children; pid_ptr++, error_pipe++) {
      err = wait_and_handle_errors(*pid_ptr);
      // закрываем на чтение каналы ошибок
      close_pipe_end((*error_pipe)[0]);
    }
  }

  if (0 != *executable_pid) {
    free(executable_pid);
  }

  return err;
}
