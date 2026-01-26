#include "abonent_dir.h"

int field_input(char field[FIELD_SIZE]) {
  char buf[BUFSIZ];
  int i = 0, n = FIELD_SIZE - 1;

  if (NULL == fgets(buf, sizeof(buf), stdin)) {
    printf("Ошибка при чтении данных.");
    return 1;
  }
  if ('\n' == buf[0]) {
    printf(
        "Ошибка: Кажется ничего не введено.\n"
        "Пожалуйста, введите хоть что-нибудь.\n");
    return 2;
  }

  while ('\n' != buf[i] && i < BUFSIZ) {
    i++;
  }
  buf[i] = '\0';  // заменяем перенос строки на конец строки
                  // Возможно надо поколдовать с вводом на Windows и Mac,
                  // но я не проверял за неимением оных под рукой.
  if (i > n) {
    printf(
        "Ошибка: Введённые данные больше %d байт.\n"
        "Введите до %d символов латиницы или до %d "
        "символов кириллицы.\n",
        n, n, n / 2);
    return 3;
  }

  while (i >= 0) {
    field[i] = buf[i];
    i--;
  }
  return 0;
}
