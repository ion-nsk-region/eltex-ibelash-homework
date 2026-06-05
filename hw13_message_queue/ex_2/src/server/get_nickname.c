#include "mq_chat.h"

int get_nickname(char *mtext, char *nickname, size_t *nickname_length) {
  int err = 0;
  char *nickname_ptr = nickname, *mtext_ptr = mtext;

  if (NULL == mtext_ptr) {
    fprintf(stderr, "Ошибка: сообщение не содержит никнейма.\n");
    err = -1;
  }
  if (NULL == nickname_ptr) {
    fprintf(stderr, "Ошибка: не указана выходная переменная для никнейма.\n");
    err = -1;
  }
  if (NULL == nickname_length) {
    fprintf(stderr,
            "Ошибка: не указана выходная переменная для длины никнейма.\n");
    err = -1;
  }

  if (0 == err) *nickname_length = 0;
  while (0 == err && '\0' != *mtext_ptr &&
         MAX_NICKNAME_LENGTH > *nickname_length) {
    *nickname_ptr = *mtext_ptr;
    mtext_ptr++;
    nickname_ptr++;
    (*nickname_length)++;
  }
  if (0 == err) *nickname_ptr = '\0';

  if (2 > *nickname_length || MAX_NICKNAME_LENGTH <= *nickname_length) {
    fprintf(
        stderr,
        "Ошибка: длина ника должна быть от 2 до %d байт. Введено байт: %zu.\n",
        (MAX_NICKNAME_LENGTH - 1), (strlen(mtext)));
    err = -1;
  }

  return err;
}
