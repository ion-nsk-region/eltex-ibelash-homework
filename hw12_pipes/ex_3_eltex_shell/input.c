#include "eltex_shell.h"

int input(char user_input[BUFSIZ], int *n_pipes, int *n_words) {
  int err = 0;
  *n_words = 0;
  *n_pipes = 0;

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
        (*n_words)++;
        is_in_a_word = 1;
      }
      if ('|' == *p) (*n_pipes)++;
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
