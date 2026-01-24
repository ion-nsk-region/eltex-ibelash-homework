/// \file
/// \brief Тестирование функций.
/// \authors Иван Белаш
/// \date 2026-01-24

#include "abonent_dir.h"

// ====================================================================
/*! \brief Главная функция.
 *
 * Здесь вызываются тестируемые функции.
 *
 * \return Код ошибки, где:
 * - 0 - всё хорошо;
 */
int main() {
  struct Directory *directory =
      (struct Directory *)malloc(sizeof(struct Directory));
  directory->head = NULL;
  directory->tail = NULL;
  directory->size = 0;

  abonent_add(directory);

  printf("Name: %s LName: %s Tel: %s\n", directory->head->name, directory->head->second_name, directory->head->tel);

  return 0;
}
// ====================================================================
