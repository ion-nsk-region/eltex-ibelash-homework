#include "abonent_dir.h"

void list_all_abonents(struct Directory *dir) {
  if (0 != dir->size) {
    struct Abonent *current = dir->head;

    printf("Размер справочника: %d\n", dir->size);
    printf("№:  Имя:       Фамилия:   Телефон:\n");
    for (int i = 0; i < dir->size; i++) {
      printf("%3d", i);
      abonent_print(*current);
      current = current->next;
    }
  } else {
    printf("Справочник пуст.");
  }
  printf("\n");
}
