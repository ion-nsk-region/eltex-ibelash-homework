#include "eltex_shell.h"

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
    int is_in_a_word = 0;
    while ('\n' != *p && p - user_input < BUFSIZ) {
      // считаем слова
      if (' ' == *p || '\t' == *p)
        is_in_a_word = 0;
      else if (0 == is_in_a_word) {
        (*user_input_length)++;
        is_in_a_word = 1;
      }
      p++;
    }
    if (BUFSIZ == p - user_input && '\n' != *p) {
      // Пользовательский ввод больше буфера, требуется повторное чтение
      err = -3;
    } else {
      // заменяем перенос строки на конец строки
      *p = '\0';
    }
  }

  return err;
}
