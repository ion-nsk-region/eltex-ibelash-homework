#include "abonent_dir.h"

int abonent_add(struct Abonent directory[DIR_SIZE]) {
  struct Abonent new_abonent;
  int index;

  printf("Введите имя: ");
  if (0 != field_input(new_abonent.name)) {
    printf("Новая запись не создана. Попробуйте снова.\n");
    return 1;
  }

  printf("Введите фамилию: ");
  if (0 != field_input(new_abonent.second_name)) {
    printf("Новая запись не создана. Попробуйте снова.\n");
    return 2;
  }

  printf("Введите телефон: ");
  if (0 != field_input(new_abonent.tel)) {
    printf("Новая запись не создана. Попробуйте снова.\n");
    return 3;
  }

  index = abonent_search(directory, "000000000\0", 0);
  // Мы предполагаем что никто не станет вводить имя из одних только нулей

  for (int i = 0; i < FIELD_SIZE - 1; i++) {
    directory[index].name[i] = new_abonent.name[i];
    directory[index].second_name[i] = new_abonent.second_name[i];
    directory[index].tel[i] = new_abonent.tel[i];
  }

  return 0;
}

