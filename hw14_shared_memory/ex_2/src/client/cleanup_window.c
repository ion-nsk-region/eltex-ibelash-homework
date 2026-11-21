#include "client_ui.h"

int cleanup_window(WINDOW *win) {
  int ret = 0;
  if (NULL != win) {
    ret = delwin(win);
    if (ERR == ret) {
      fprintf(stderr, "Не удалось очистить память окна %p\n", win);
    }
  }
  return ret;
}
