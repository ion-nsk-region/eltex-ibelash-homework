#include "abonent_dir.h"

int menu() {
  int item, ret, c;
  printf("\n1) Добавить абонента\n");
  printf("2) Удалить абонента\n");
  printf("3) Поиск абонентов по имени\n");
  printf("4) Вывод всех записей\n");
  printf("5) Выход\n");

  ret = scanf("%d", &item);
  // очищаем буфер stdin чтобы не было срабатываний на некорректный ввод
  while('\n' != (c = getchar()) && EOF != c);  

  if (1 != ret) {
    return -1;
  }

  if (item < 1 || item > 5) {
    return -1;
  }
  return item;
}
