#include "client_ui.h"

int cleanup_window(WINDOW *win) {
  int ret = delwin(win);
  if (ERR == ret) {
    fprintf(stderr, "Не удалось очистить память окна %p\n", win);
  }
  return ret;
}
