#include "abonent_dir.h"

int abonent_search(struct Abonent directory[DIR_SIZE], char name[FIELD_SIZE],
                   int start) {
  for (int i = start; i < DIR_SIZE; i++) {
    if (0 == string_compare(name, directory[i].name)) {
      return i;
    }
  }
  return -1;  // ничего не найдено
}
