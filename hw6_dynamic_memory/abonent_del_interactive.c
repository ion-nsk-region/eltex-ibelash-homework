#include "abonent_dir.h"

int abonent_del_interactive(struct Abonent directory[DIR_SIZE]) {
  int id;
  printf("Пожалуйста, укажите id абонента для удаления: ");
  if (1 != scanf("%d", &id)) {
    printf("Ошибка: введено не число.");
    return 1;
  }
  if (-1 >= id || DIR_SIZE <= id) {
    printf("Ошибка: id за пределами возможных значений от 0 до %d\n", DIR_SIZE);
    return 2;
  }
  // Мы предполагаем, что FIELD_SIZE равно 10, отсюда такие "нулевые" строки
  if (0 == string_compare(directory[id].name, "000000000\0") &&
      0 == string_compare(directory[id].second_name, "000000000\0") &&
      0 == string_compare(directory[id].tel, "000000000\0")) {
    printf("Пустая запись. Уже удалено?\n");
    return 3;
  }

  abonent_del(&directory[id]);
  return 0;
}
