#include "./libs/calc.h"

int main(void) {
  int menu_item = 0, n_items = 0, menu_exit, ret = 0;
  char *func_names[FUNC_MAX], *menu_names[FUNC_MAX];
  void *func_handles[FUNC_MAX];

  ret = load_plugins(func_handles, func_names, menu_names, &n_items);
  if (0 > ret) {
    printf("Ошибка во время загрузки плагинов.\n");
  }

  menu_exit = n_items + 1;

  while (menu_exit != menu_item) {
    menu_item = menu(menu_names, n_items);

    if (MENU_ERROR == menu_item) {
      printf(
            "Ошибка: Такого пункта меню не существует.\n"
            "        Пожалуйста, введите только одну цифру.\n");
        continue;
    } else if(menu_exit == menu_item) {
        printf("Выходим.\n");
        continue;
    }
    
    printf("Выполняем %s\n", menu_names[menu_item]);
    run_operation(func_handles[menu_item], func_names[menu_item]);
    
  }

  // unload_plugins();

  return 0;
}
