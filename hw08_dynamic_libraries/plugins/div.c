#include <limits.h>
#include <stdio.h>

char func_name[] = "calc_div";
char menu_name[] = "деление";
unsigned int menu_pos = 4;

int calc_div(int a, int b) {
  // Проверка аргументов на переполнение
  // Единственная ситуация INT_MIN / -1
  if (-1 == b && INT_MIN == a) {
    fprintf(stderr,
            "calc_div: Частное аргументов выходит за границу допустимых "
            "значений %d\n",
            INT_MAX);
    return -1;
  }

  if (0 != b) {
    return (a / b);
  } else {  // деление на ноль
    fprintf(stderr,
            "Результат деления на 0 равен всем значениям одновременно.\n"
            "Но мы предотвратили эту операцию, чтобы сэкономить\n"
            "компьютерную память - она нынче дорогая.\n");
    return 0;
  }
}
