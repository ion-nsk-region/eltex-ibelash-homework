#include "eltex_shell.h"

int main(void) {
  char is_running = 1;  // статус самой оболочки
  int err;
  do {
    char user_input[BUFSIZ];
    int **exec_err = NULL, **exec_pipe = NULL, n_pipes = 0, n_words = 0;
    char ***arguments = NULL;

    err = 0;

    printf("\nВведите команду для запуска и её аргументы: ");
    if (0 > (err = input(user_input, &n_pipes, &n_words))) {
      // TODO сделать обработку очень длинного ввода, когда аргументов больше
      // чем BUFSIZ (err = -3)
      fprintf(stderr, "Ошибка ввода %d. Попробуйте снова.\n", err);
    }

    if (0 == err) {
      arguments = (char ***)malloc((n_pipes + 1) * sizeof(char **));
      if (-1 ==
          parse_multiple_commands(user_input, n_pipes, n_words, &arguments)) {
        fprintf(stderr,
                "Ошибка: не удалось разобрать аргументы. Попробуйте снова.\n");
        err -= 1;
      }
      // TODO починить парсинг аргументов для встроенных команд
      if (0 == strcmp("exit", **arguments)) is_running = 0;
      if (0 == strcmp("cd", **arguments)) {
        err = elt_cd(*arguments);
        if (0 == err) err = 1;  // убираем запуск дочернего процесса
      }
    }

    if (0 == err && is_running) {
      err = create_pipes(&exec_err, n_pipes + 1);
      if (0 == err) err = create_pipes(&exec_pipe, n_pipes);
    }

    if (0 == err && is_running) {
      err = spawn_children(arguments, n_pipes, exec_err, exec_pipe);
    }


    if (NULL != arguments) {
      // TODO высвободить память из-под указателей на отдельные команды
      free(arguments);
      arguments = NULL;
    }
    if (NULL != exec_err) {
      for (int **p = exec_err; p - exec_err <= n_pipes; p++) {
        if (NULL != p && NULL != *p) {
          free(*p);
        }
      }
      free(exec_err);
      exec_err = NULL;
    }
    if (NULL != exec_pipe) {
      for (int **p = exec_pipe; p - exec_pipe < n_pipes; p++) {
        if (NULL != p && NULL != *p) {
          free(*p);
        }
      }
      free(exec_pipe);
      exec_pipe = NULL;
    }
  } while (is_running && 0 == err);

  return err;
}
