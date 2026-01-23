#include "abonent_dir.h"

int menu() {
  int item;
  printf("\n1) Добавить абонента\n");
  printf("2) Удалить абонента\n");
  printf("3) Поиск абонентов по имени\n");
  printf("4) Вывод всех записей\n");
  printf("5) Выход\n");

  if (1 != scanf("%d", &item)) {
    return -1;
  }
  scanf("%*c");  // считываем и выбрасываем перенос строки из буфера

  if (item < 1 || item > 5) {
    return -1;
  }
  return item;
}
