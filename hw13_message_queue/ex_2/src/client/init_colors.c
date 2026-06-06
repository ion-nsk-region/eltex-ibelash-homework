#include "client.h"
#include "client_ui.h"

int init_colors(void) {
  int return_val = 0;
  if (has_colors() == FALSE) {
    endwin();
    printf("Your terminal does not support color\n");
    return_val = -1;
  } else {
    start_color();

    init_pair(1, COLOR_WHITE, COLOR_BLACK);
    init_pair(2, COLOR_CYAN, COLOR_BLACK);
    init_pair(3, COLOR_RED, COLOR_BLUE);
  }

  return return_val;
}
