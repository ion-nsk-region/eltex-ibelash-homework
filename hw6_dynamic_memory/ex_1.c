/// \file
/// \brief Единственный файл.
/// \details Здесь реализована вся функциональность справочника.
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
  struct Abonent directory[DIR_SIZE];
  int directory_size = 0;
  int menu_item = 0;

  clear_dir(directory);

  while (5 != menu_item) {
    menu_item = menu();

    switch (menu_item) {
      case -1:
        printf(
            "Ошибка: Такого пункта меню не существует.\n"
            "        Пожалуйста введите только одну цифру.\n");
        break;
      case 1:
        if (100 <= directory_size) {
          printf(
              "Ошибка: Превышен допустимый размер справочника.\n"
              "        Пожалуйста, удалите лишние записи.\n");
          break;
        }
        if (0 == abonent_add(directory)) {
          directory_size++;
        }
        break;
      case 2:
        if (0 == abonent_del_interactive(directory)) {
          directory_size--;
        }
        break;
      case 3:
        if (0 >= directory_size) {
          printf("Справочник пуст.\n");
          break;
        }
        if (0 != directory_search(directory, directory_size)) {
          printf("Ошибка: Неверный ввод. Пожалуйста, введите снова.");
        }
        break;
      case 4:
        if (0 < directory_size) {
          list_all_abonents(directory);
          printf("Всего абонентов: %d\n", directory_size);
        } else {
          printf("Справочник пуст.\n");
        }
        break;
      case 5:
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

