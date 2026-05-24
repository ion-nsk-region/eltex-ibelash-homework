#include "mq_chat.h"

void wait_for_quit(void) {
  int keyboard_input;
  do {
    printf("Нажмите 'q' для завершения работы.\n");
    keyboard_input = getchar();
    int tmp;
    while ('\n' != (tmp = getchar()) && EOF != tmp);
  } while ('q' != keyboard_input);
}
