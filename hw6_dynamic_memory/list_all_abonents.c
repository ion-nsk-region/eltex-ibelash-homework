#include "abonent_dir.h"

void list_all_abonents(struct Abonent directory[DIR_SIZE]) {
  printf("id: Имя:       Фамилия:   Телефон:\n");
  for (int i = 0; i < DIR_SIZE; i++) {
    if (1 == string_compare(directory[i].name, "000000000\0")) {
      printf("%3d ", i);
      abonent_print(directory[i]);
    }
  }
}
