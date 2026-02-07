#include "calc.h"

int main(void) {
  int menu_item = 0, n_items = 0, menu_exit;
  char *func_names[FUNC_MAX], *menu_names[FUNC_MAX], *error;
  void *func_handles[FUNC_MAX];

  load_plugins(func_handles, func_names, menu_names, &n_items);

  menu_exit = n_items + 1;

  while (menu_exit != menu_item) {
    menu_item = menu();

    if (MENU_ERROR == menu_item) {
      printf(
            "Ошибка: Такого пункта меню не существует.\n"
            "        Пожалуйста, введите только одну цифру.\n");
        continue;
    } else if(menu_exit == menu_item) {
        printf("Выходим.\n");
        continue;
    }
    
    run_operation();
    
  }

  unload_plugins();

  return 0;
}
