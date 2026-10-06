#include <wctype.h>

#include "client.h"

void handle_input(struct ui ui, int server_mq_id, int ch, char *input_buf,
                  size_t *input_buf_length) {
  size_t max_msg_size = get_max_msg_size() - sizeof(struct chat_msg);
  switch (ch) {
    case KEY_ENTER:
    case '\r':
    case '\n':
      on_key_enter(ui, server_mq_id, input_buf, input_buf_length);
      break;
    case KEY_RESIZE:  // TODO перейти в input с getchar на wgetch
                      // чтобы обрабатывать изменение размера терминала.
      handle_resize(ui);
      break;
    case '\x7F':  // DEL более известный как Backspace на современных
                  // клавиатурах и терминалах
      on_key_backspace(ui, input_buf, input_buf_length);
      break;
    default:
      if (iswprint(ch) && *input_buf_length < (max_msg_size - 1)) {
        waddch(ui.msg_input, ch);
        // Дополняем буфер сообщения для отправки
        *(input_buf + *input_buf_length) = ch;
        ++(*input_buf_length);
        *(input_buf + *input_buf_length) = '\0';

      } else {
        //  wprintw(ui.msg_input, " k=%d", ch);
      }
  }
}
