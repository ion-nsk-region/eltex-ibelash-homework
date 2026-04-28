#include "eltex_shell.h"

int spawn_single_child(char ***arg_ptr, int *exec_pipe_in, int *exec_pipe_out,
                       int **error_pipe_ptr, pid_t *pid_ptr) {
  int err = 0;

  errno = 0;
  *pid_ptr = fork();
  if (-1 == *pid_ptr) {
    perror("fork");
    err -= 1;
  } else if (0 == *pid_ptr) {
    // Дочерний процесс:
    // - конфигурируем каналы
    if (0 == err) {
      err = configure_child_channels(exec_pipe_in, exec_pipe_out);
    }
    // - запускаем наш исполняемый файл
    if (0 == err) {
      err = run_executable(*arg_ptr, *error_pipe_ptr);
    } else {
      fprintf(stderr,
              "Не удалось запустить процесс %s так как не были настроены "
              "каналы. Код ошибки %d.\n",
              **arg_ptr, err);
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
  }

  return err;
}
