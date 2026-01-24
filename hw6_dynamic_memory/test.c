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
  struct Abonent *abonent;
  char name[FIELD_SIZE];
  int res = 0;

  directory->head = NULL;
  directory->tail = NULL;
  directory->size = 0;

  abonent_add(directory);
  abonent_add(directory);
  list_all_abonents(directory);

  printf("Введите имя для поиска: ");
  res = field_input(name);
  if (0 != res) {
    return res;
  }
  abonent = abonent_search(directory->head, name);
  if(NULL != abonent) abonent_print(*abonent);
  printf("Введите имя для поиска: ");
  res = field_input(name);
  if (0 != res) {
    return res;
  }
  abonent = abonent_search(directory->head, name);
  if(NULL != abonent) abonent_print(*abonent);

  abonent_del(directory, directory->head);
  abonent_del(directory, directory->head);

  free(directory->head);
  free(directory);
  directory = NULL;

  return 0;
}
// ====================================================================
