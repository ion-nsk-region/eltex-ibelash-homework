#include <limits.h>
#include <stdio.h>

char func_name[] = "calc_add";
char menu_name[] = "сложение";
unsigned int menu_pos = 1;

int calc_add(int a, int b) {
  if ((0 < b && INT_MAX - b < a) || (0 > b && INT_MIN - b > a)) {
    fprintf(stderr,
            "calc_add: Сумма аргументов выходит за границы допустимых значений "
            "%d..%d\n",
            INT_MIN, INT_MAX);
    return -1;
  }

  return (a + b);
}
