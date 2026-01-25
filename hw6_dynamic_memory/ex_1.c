/// \file
/// \brief Главный файл.
/// \details Здесь реализована только главная функция, а другая
/// функциональность справочника лежит в остальных файлах проекта.
/// \authors Иван Белаш
/// \date 2025-12-03
/// \warning Данный справочник создан только в учебных целях

#include "abonent_dir.h"

// ====================================================================
/*! \brief Главная функция.
 *
 * Здесь в бесконечном цикле крутится консольное меню и вызываются
 * другие функции в зависимости от выбранных пунктов меню.
 *
 * \note Поговаривают, что так же называется карман номер ноль
 * жилетки Анатолия Вассермана.
 * \return Код ошибки, где:
 * - 0 - всё хорошо;
 * - других значений пока нет, так как все ошибки выводятся на экран
 * и программа продолжает выполняться до победного выхода.
 */
int main() {
  struct Directory *directory =
      (struct Directory *)malloc(sizeof(struct Directory));
  directory->head = NULL;
  directory->tail = NULL;
  directory->size = 0;
  int menu_item = 0;

  //  clear_dir(directory);

  while (5 != menu_item) {
    menu_item = menu();

    switch (menu_item) {
      case MENU_ERROR:
        printf(
            "Ошибка: Такого пункта меню не существует.\n"
            "        Пожалуйста введите только одну цифру.\n");
        break;
      case MENU_ADD:
        if (MAX_DIR_SIZE <= directory->size) {
          printf(
              "Ошибка: Превышен допустимый размер справочника.\n"
              "        Пожалуйста, удалите лишние записи.\n");
          break;
        }
        if (0 == abonent_add(directory)) {
          directory->size++;
        }
        break;
      case MENU_DEL:
        if (0 == abonent_del_interactive(directory)) {
          directory->size--;
        }
        break;
      case MENU_SEARCH:
        if (0 >= directory->size) {
          printf("Справочник пуст.\n");
          break;
        }
        if (0 != directory_search(directory)) {
          printf("Ошибка: Неверный ввод. Пожалуйста, введите снова.");
        }
        break;
      case MENU_LIST_ALL:
        if (0 < directory->size) {
          list_all_abonents(directory);
          printf("Всего абонентов: %d\n", directory->size);
        } else {
          printf("Справочник пуст.\n");
        }
        break;
      case MENU_EXIT:
  //  clear_dir(directory);
        printf("Выходим.\n");
        break;
      default:
        printf("Ошибка: Пункт меню %d) всё ещё в разработке.\n", menu_item);
        printf("        Пожалуйста, выберите другой пункт меню.\n");
        break;
    }
  }

  return 0;
}
// ====================================================================
