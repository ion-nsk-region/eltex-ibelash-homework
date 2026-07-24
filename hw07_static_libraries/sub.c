#include "calc.h"

void calc_sub(void) {
  int a, b;

  while (0 != calc_input(&a, &b)) {
    printf("Попробуйте снова.\n\n");
  }
  // TODO Проверка аргументов на переполнение снизу

  printf("%d\n", (a - b));
}
