#include "eltex_shell.h"

int main(void) {
  char is_running = 1;
  int err;
  do {
    char user_input[BUFSIZ];
    int exec_err[2], user_input_length;
    char **arguments = NULL;

    err = 0;

    // читаем команду и её аргументы
    printf("\nВведите команду для запуска и её аргументы: ");
    if (0 > (err = input(user_input, &user_input_length))) {
      // TODO сделать обработку очень длинного ввода, когда аргументов больше
      // чем BUFSIZ (err = -3)
      fprintf(stderr, "Ошибка ввода %d. Попробуйте снова.\n", err);
    }

    if (0 == err) {
      arguments = (char **)malloc((user_input_length + 1) * sizeof(char *));
      if (0 == parse_input(user_input, user_input_length, arguments)) {
        fprintf(stderr,
                "Ошибка: не удалось разобрать аргументы. Попробуйте снова.\n");
        err -= 1;
      }
      if (0 == strcmp("exit", arguments[0])) is_running = 0;
      if (0 == strcmp("cd", arguments[0])) {
        err = elt_cd(arguments);
        if (0 == err) err = 1;  // убираем запуск дочернего процесса
      }
    }

    // делаем канал, чтобы возвращать код ошибки от exec
    // позаимствовано отсюда:
    // https://acm.bsu.by/wiki/Unix2018/%D0%A2%D0%B5%D1%85%D0%BD%D0%B8%D0%BA%D0%B0_fork_%E2%80%94_exec#.D0.A0.D0.B5.D1.88.D0.B5.D0.BD.D0.B8.D0.B5_.D0.BF.D1.80.D0.BE.D0.B1.D0.BB.D0.B5.D0.BC.D1.8B_.D0.BE.D1.82.D0.BB.D0.BE.D0.B2.D0.B0_.D0.BE.D1.88.D0.B8.D0.B1.D0.BA.D0.B8_exec
    if (0 == err && is_running) {
      err = pipe4exec_err(exec_err);
      if (0 > err) {
        fprintf(stderr,
                "Ошибка: не удалось создать канал для чтения ошибок запуска "
                "дочерних процессов. Код ошибки: %d\n",
                err);
      }
    }

    if (0 == err && is_running) {
      // запускаем дочерний процесс
      errno = 0;
      pid_t executable_pid = fork();
      if (-1 == executable_pid) {
        perror("fork");
        err -= 1;
      } else if (0 < executable_pid) {
        // Родительский процесс:
        err = wait_and_handle_errors(executable_pid, exec_err);
      } else if (0 == executable_pid) {
        // Дочерний процесс:
        err = run_executable(arguments, exec_err);
      }
    }
    if (NULL != arguments) free(arguments);
  } while (is_running);

  return err;
}
