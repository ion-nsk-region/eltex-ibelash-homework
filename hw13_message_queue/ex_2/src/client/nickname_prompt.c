#include "client.h"

int nickname_prompt(int server_mq_id) {
  char nickname[MAX_NICKNAME_LENGTH] = {}, input_buffer[BUFSIZ] = {};
  int err = 0;
  pid_t my_pid = getpid();

  int n_attempts = 0;
  size_t nickname_length = 0;

  while (3 > n_attempts &&
         !(MAX_NICKNAME_LENGTH > nickname_length && 3 <= nickname_length)) {
    err = 0;
    nickname_length = 0;
    printf("Пожалуйста, введите свой никнейм (от 3 до %d символов): ",
           (MAX_NICKNAME_LENGTH - 1));
    if (NULL == fgets(input_buffer, sizeof(input_buffer), stdin)) {
      fprintf(stderr, "Ошибка при чтении данных.");
      err = -1;
    }
    if (0 == err && '\n' == *input_buffer) {
      fprintf(stderr,
              "Ошибка: Кажется ничего не введено.\n"
              "Пожалуйста, введите хоть что-нибудь.\n");
      err = -1;
    }

    if (0 == err) {
      char *nick_ptr = input_buffer;
      while ('\n' != *nick_ptr && nick_ptr - input_buffer < BUFSIZ) {
        ++nick_ptr;
      }
      *nick_ptr = '\0';

      nickname_length = nick_ptr - input_buffer;
      if (MAX_NICKNAME_LENGTH < nickname_length || 3 > nickname_length) {
        fprintf(stderr,
                "Ошибка: длина ника должна быть от 3 до %d байт. "
                "Введено байт: %zu.\n",
                (MAX_NICKNAME_LENGTH - 1), nickname_length);
        err = -1;
      } else {
        strncpy(nickname, input_buffer, nickname_length);
      }
    }

    ++n_attempts;
  }

  if (0 == err) {  // подключаемся к чату
    struct chat_msg join_msg = {my_pid, JOIN, nickname};
    if (0 != (err = send_mq_msg(server_mq_id, 1, join_msg))) {
      printf("Ошибка send_mq_msg: %d\n", err);
    }
  }

  return err;
}
