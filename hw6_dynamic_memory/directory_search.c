#include "abonent_dir.h"

int directory_search(struct Abonent directory[DIR_SIZE], int dir_size) {
  int index = 0, res;
  char name[FIELD_SIZE];
  printf("Введите имя для поиска: ");
  res = field_input(name);
  if (0 != res) {
    return res;
  }

  printf("id: Имя:       Фамилия:   Телефон:\n");

  for (int i = 0; i < dir_size; i++) {
    index = abonent_search(directory, name, index);
    if (-1 == index) {
      break;
    }
    printf("%3d ", index);
    abonent_print(directory[index]);
    index++;
  }
  printf("\n");
  return 0;
}
