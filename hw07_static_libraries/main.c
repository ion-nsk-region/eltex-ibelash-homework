#include "calc.h"

int main(void) {
  int menu_item = 0;

  while (MENU_EXIT != menu_item) {
    menu_item = menu();

    switch (menu_item) {
      case MENU_ERROR:
        printf(
            "Ошибка: Такого пункта меню не существует.\n"
            "        Пожалуйста, введите только одну цифру.\n");
        break;
      case MENU_ADD:
        printf("Выполняем сложение\n");
        calc_add();
        break;
      case MENU_SUB:
        printf("Выполняем вычитание\n");
        calc_sub();
        break;
      case MENU_MUL:
        printf("Выполняем умножение\n");
        calc_mul();
        break;
      case MENU_DIV:
        printf("Выполняем деление\n");
        calc_div();
        break;
      case MENU_EXIT:
        printf("Выходим.\n");
        break;
      default:
        printf(
            "Ошибка: Пункт меню %d) всё ещё в разработке.\n"
            "        Пожалуйста, выберите другой пункт меню.\n",
            menu_item);
        break;
    }
  }
  return 0;
}
