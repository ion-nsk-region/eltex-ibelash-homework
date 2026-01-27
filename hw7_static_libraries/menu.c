#include "calc.h"

int menu() {
  int item, ret, c;
  printf("\n1) Сложение\n");
  printf("2) Вычитание\n");
  printf("3) Умножение\n");
  printf("4) Деление\n");
  printf("5) Выход\n");

  ret = scanf("%d", &item);
  // очищаем буфер stdin чтобы не было срабатываний на некорректный ввод
  while('\n' != (c = getchar()) && EOF != c);  

  if (1 != ret) {
    return -1;
  }

  if (item < MENU_ADD || item > MENU_EXIT) {
    return -1;
  }

  return item;
}
