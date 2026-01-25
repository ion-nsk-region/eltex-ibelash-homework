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
  int res = 0;

  directory->head = NULL;
  directory->tail = NULL;
  directory->size = 0;

  abonent_add(directory);
  abonent_add(directory);
  abonent_add(directory);
  list_all_abonents(directory);

  res = directory_search(directory);
  printf("Результат поиска: %d\n", res);

  abonent_del(directory, directory->head);
  abonent_del(directory, directory->head);

  free(directory->head);
  free(directory);
  directory = NULL;

  return 0;
}
// ====================================================================
