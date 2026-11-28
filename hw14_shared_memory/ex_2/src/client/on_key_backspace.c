#include "client.h"

void on_key_backspace(WINDOW *input, char *input_buf,
                      size_t *input_buf_length) {
  if (0 < *input_buf_length) {
    *(input_buf + *input_buf_length - 1) = '\0';
    --(*input_buf_length);
    int y, x;
    getyx(input, y, x);
    if (0 < x) {
      mvwdelch(input, y, x - 1);
    } else if (1 < y) {
      int max_x = getmaxx(input);
      mvwdelch(input, y - 1, max_x - 1);
    }
  }
}
