#include <limits.h>
#include <stdio.h>

char func_name[] = "calc_mul";
char menu_name[] = "умножение";
unsigned int menu_pos = 3;

int calc_mul(int a, int b) {
  if ((-1 == b && INT_MIN == a) || (-1 == a && INT_MIN == b) ||
      (((0 < b && 0 < a) || (0 > b && 0 > a)) && INT_MAX / b < a) ||
      ((0 < b && 0 > a) && INT_MIN / b > a) ||
      ((0 > b && 0 < a) && INT_MIN / a > b)) {
    fprintf(stderr,
            "calc_mul: Произведение аргументов выходит за границы допустимых "
            "значений %d..%d\n",
            INT_MIN, INT_MAX);
    return -1;
  }

  return (a * b);
}
