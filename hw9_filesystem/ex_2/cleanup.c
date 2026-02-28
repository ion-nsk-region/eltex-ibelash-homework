#include "eltex_commander.h"

int cleanup(WINDOW *left_panel, WINDOW *right_panel) {
  int ret = 0;
  ret = delwin(left_panel);
  if (ERR == ret) {
    fprintf(stderr, "Не удалось очистить память левой панели.\n");
    return ret;
  }

  ret = delwin(right_panel);
  if (ERR == ret) {
    fprintf(stderr, "Не удалось очистить память правой панели.\n");
    return ret;
  }

  ret = endwin();
  if (ERR == ret) {
    fprintf(stderr,
            "Не удалось вернуть настройки терминала в исходное состояние.\n"
            "Рекомендуем перезапустить терминал.\n");
    return ret;
  }

  return 0;
}
