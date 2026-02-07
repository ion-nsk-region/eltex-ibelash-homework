#include "calc.h"

int menu(char *menu_names[FUNC_MAX], int n_items) {
  int item, ret, c, item_exit = n_items + 1;

  for(int i = 1; i <= n_items, i++) {
    printf("%d) %s\n", i, *menu_names[i]);
  }
  printf("%d) Выход\n", item_exit);

  ret = scanf("%d", &item);
  // очищаем буфер stdin чтобы не было срабатываний на некорректный ввод
  while('\n' != (c = getchar()) && EOF != c);  

  if (1 != ret) {
    return MENU_ERROR;
  }

  if (0 > item || item_exit < item) {
    return MENU_ERROR;
  }

  return item;
}
