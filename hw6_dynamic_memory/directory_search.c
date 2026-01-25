#include "abonent_dir.h"

int directory_search(struct Directory *dir) {
  int res;
  char name[FIELD_SIZE];
  struct Abonent *abonent = dir->head;

  printf("Введите имя для поиска: ");
  res = field_input(name);
  if (0 != res) {
    return res;
  }

  printf("id:  Имя:       Фамилия:   Телефон:\n");
  int i = 0;
  while(NULL != abonent) {
    i++;
    printf("%3d ", i);
    abonent = abonent_search(abonent, name);
    abonent_print(*abonent);
    abonent = abonent->next;
  }
  printf("\n");
  return 0;
}
