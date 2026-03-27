#include <errno.h>
#include <fcntl.h>
#include <limits.h>
#include <malloc.h>
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <unistd.h>

int elt_cd(char **args);
int input(char user_input[BUFSIZ], int *user_input_length);
int parse_input(char user_input[BUFSIZ], int user_input_length,
                char **arguments);
int pipe4exec_err(int *exec_err);
int run_executable(char **arguments, int *exec_err);
int wait_and_handle_errors(pid_t executable_pid, int *exec_err);

int main(void) {
  char is_running = 1;
  int err;
  do {
    char user_input[BUFSIZ];
    int exec_err[2], user_input_length;
    char **arguments = NULL;

    err = 0;

    // читаем команду и её аргументы
    printf("Введите команду для запуска и её аргументы:\n");
    if (0 > (err = input(user_input, &user_input_length))) {
      // TODO сделать обработку очень длинного ввода, когда аргументов больше
      // чем BUFSIZ (err = -3)
      fprintf(stderr, "Ошибка ввода %d. Попробуйте снова.\n", err);
    }

    if (0 == err) {
      arguments = (char **)malloc(user_input_length * sizeof(char *));
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

// ==========================================================================
int input(char user_input[BUFSIZ], int *user_input_length) {
  int err = 0;
  *user_input_length = 0;

  if (NULL == fgets(user_input, BUFSIZ, stdin)) {
    // ошибка во время ввода/прерванный ввод
    err = -1;
  }
  if (0 == err && '\n' == *user_input) {
    // пустой ввод/ничего не введено
    err = -2;
  }

  if (0 == err) {
    char *p = user_input;
    while ('\n' != *p && p - user_input < BUFSIZ) {
      p++;
    }
    if (BUFSIZ == p - user_input && '\n' != *p) {
      // Пользовательский ввод больше буфера, требуется повторное чтение
      err = -3;
    } else {
      // заменяем перенос строки на конец строки; считаем длину ввода
      *p = '\0';
      *user_input_length = p - user_input;
    }
  }

  return err;
}

// ==========================================================================
int parse_input(char user_input[BUFSIZ], int user_input_length,
                char **arguments) {
  if (0 == user_input_length) {
    return 0;
  }
  char **p = arguments;
  char *token = strtok(user_input, " ");

  while (NULL != token) {
    *p = token;
    p++;
    token = strtok(NULL, " ");
  }
  *p = NULL;  // последний аргумент должен быть NULL для execvp

  return p - arguments;
}

// ==========================================================================
int pipe4exec_err(int *exec_err) {
  int err = 0;
  errno = 0;
  if (-1 == pipe(exec_err)) {
    perror("pipe");
    err -= 1;
  }
  errno = 0;
  if (-1 ==
      fcntl(exec_err[1], F_SETFD, fcntl(exec_err[1], F_GETFD) | FD_CLOEXEC)) {
    perror("fcntl");
    err -= 1;
  }
  return err;
}

// ==========================================================================
int wait_and_handle_errors(pid_t executable_pid, int *exec_err) {
  int err = 0;
  // Закрываем канал на запись, только читаем
  errno = 0;
  if (-1 == close(exec_err[1])) {
    perror("close");
    err -= 1;
  }
  // Читаем и обрабатываем ошибку
  ssize_t count;
  int exec_error;
  while (-1 == (count = read(exec_err[0], &exec_error, sizeof(errno)))) {
    if (EAGAIN != errno && EINTR != errno) break;
  }
  if (count) {
    fprintf(stderr, "Ошибка: не удалось запустить команду: %s\n",
            strerror(exec_error));
  }

  // закрываем канал окончательно
  if (-1 == close(exec_err[0])) {
    perror("close");
    err -= 1;
  }

  // Ждём выхода из дочернего процесса
  int status;
  waitpid(executable_pid, &status, 0);
  if (WIFEXITED(status) && 0 != status) {
    fprintf(stderr, "Предупреждение: Команда вернула ненулевой статус: %d\n",
            WEXITSTATUS(status));
  }

  return err;
}

// ==========================================================================
int run_executable(char **arguments, int *exec_err) {
  int err = 0;
  // закрываем канал на чтение, только пишем
  errno = 0;
  if (-1 == close(exec_err[0])) {
    perror("close");
    err -= 1;
  }

  // запускаем наш исполняемый файл
  errno = 0;
  if (-1 == execvp(arguments[0], arguments)) {
    int exec_error = errno;
    perror("execvp");
    // В случае ошибки exec, возвращаем её через канал
    errno = 0;
    if (-1 == write(exec_err[1], &exec_error, sizeof(int))) {
      perror("write");
    }
    _exit(0);
  }

  return err;
}

// ==========================================================================
int elt_cd(char **args) {
  int err = 0;
  if (args[1] == NULL) {
    fprintf(stderr, "cd: отсутствует путь\n");
    err = -1;
  } else {
    errno = 0;
    if (0 != chdir(args[1])) {
      perror("cd");
    }
  }
  return err;
}
