#include <stdio.h>

char func_name[] = "calc_div";
char menu_name[] = "деление";
unsigned int menu_pos = 4;

int calc_div(int a, int b) {
  // TODO Проверка аргументов на переполнение
  // INT_MIN / -1

  if (0 != b) {
    return (a / b);
  } else {
    fprintf(stderr,
            "Результат деления на 0 равен всем значениям одновременно.\n"
            "Но мы предотвратили эту операцию, чтобы сэкономить\n"
            "компьютерную память - она нынче дорогая.\n");
    return 0;
  }
}
