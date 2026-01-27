#include "calc.h"

void calc_add(void) {
  int a, b;

  while (0 != calc_input(&a, &b)) {
    printf("Попробуйте снова.\n\n");
  }

  // TODO проверка аргументов на переполнение
  printf("%d\n", (a + b));
}
