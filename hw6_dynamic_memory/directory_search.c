#include "abonent_dir.h"

int directory_search(struct Directory *dir) {
  int res;
  char name[FIELD_SIZE];
  struct Abonent *abonent = dir->head;

  if(0 == dir->size) {
    printf("Справочник пуст.\n");
    return 0;
  }

  printf("Введите имя для поиска: ");
  res = field_input(name);
  if (0 != res) {
    return res;
  }

  // Обрабатываем первого
  abonent = abonent_search(abonent, name);
  if(NULL == abonent) {
    printf("Абоненты с именем \"%s\" не найдены.\n", name);
    return 0;
  }
  printf("№:  Имя:       Фамилия:   Телефон:\n");
  int i = 1;
  printf("%3d ", i);
  abonent_print(*abonent);
  abonent = abonent->next;

  // Обрабатываем остальных (если будут)
  while(NULL != abonent) {
    abonent = abonent_search(abonent, name);
    if(NULL != abonent) {
      i++;
      printf("%3d ", i);
      abonent_print(*abonent);
      abonent = abonent->next;
    }
  }

  return 0;
}
