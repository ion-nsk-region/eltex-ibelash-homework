#include "abonent_dir.h"

#define L_SIZE 2  // два байта для одной буквы в случае кириллицы

int yesno(void) {
  char buf[BUFSIZ];
  int i = 0, response;

  printf(" (д/Н): ");

  if (NULL == fgets(buf, sizeof(buf), stdin)) {
    printf("Ошибка при чтении данных.\n");
    return -1;
  }

  if ('\n' == buf[0]) { // действие по умолчанию
    response = 0;
  } else if ('y' == buf[0] || 'Y' == buf[0] || 1 == buf[0]) {
    response = 1;
  } else if ('n' == buf[0] || 'N' == buf[0] || 0 == buf[0]) {
    response = 0;
  } else {  // обработка Кириллицы
    while ('\n' != buf[i] && i < L_SIZE) {
      i++;
    }
    buf[i] = '\0';  // заменяем перенос строки на конец строки
                    // и обрезаем всё, что было введено далее.
    if (0 == string_compare(buf, "д\0") || 
        0 == string_compare(buf, "Д\0")) {
      response = 1;
    } else if (0 == string_compare(buf, "н\0") ||
               0 == string_compare(buf, "Н\0")) {
      response = 0;
    } else {
      printf("Недопустимый ответ: \"%.*s\". Допустимые ответы: 10yYnNдДнН\n", L_SIZE + 1, buf);
      response = -2;
    }
  }

  return response;
}
