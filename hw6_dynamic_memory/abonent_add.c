#include "abonent_dir.h"

int abonent_add(struct Directory *directory) {
  if (NULL == directory) {
    return -1;
  }
  struct Abonent *new_abonent =
      (struct Abonent *)malloc(sizeof(struct Abonent));
  if (NULL == new_abonent) {
    printf("Новая запись не создана: Не удалось выделить память.\n"
           "Попробуйте снова.\n");
    return -2;
  }

  printf("Введите имя: ");
  if (0 != field_input(new_abonent->name)) {
    printf("Новая запись не создана: Ошибка при вводе имени.\n"
           "Попробуйте снова.\n");
    free(new_abonent);
    return 1;
  }

  printf("Введите фамилию: ");
  if (0 != field_input(new_abonent->second_name)) {
    printf("Новая запись не создана: Ошибка при вводе фамилии.\n"
           "Попробуйте снова.\n");
    free(new_abonent);
    return 2;
  }

  printf("Введите телефон: ");
  if (0 != field_input(new_abonent->tel)) {
    printf("Новая запись не создана: Ошибка при вводе телефона.\n"
           "Попробуйте снова.\n");
    free(new_abonent);
    return 3;
  }

  new_abonent->prev = directory->tail;
  new_abonent->next = NULL;

  if (NULL == directory->head) {
    directory->head = new_abonent;
  }
  if (NULL != directory->tail) {
    directory->tail->next = new_abonent;
  }
  directory->tail = new_abonent;
  directory->size++;

  return 0;
}
