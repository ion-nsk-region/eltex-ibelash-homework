#include <limits.h>
#include <stdio.h>

char func_name[] = "calc_sub";
char menu_name[] = "вычитание";
unsigned int menu_pos = 2;

int calc_sub(int a, int b) {
  if ((0 < b && INT_MIN + b > a) || (0 > b && INT_MAX + b < a)) {
    fprintf(stderr,
            "calc_sub: Разность аргументов выходит за границы допустимых "
            "значений %d..%d\n",
            INT_MIN, INT_MAX);
    return -1;
  }

  return (a - b);
}
