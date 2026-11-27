#include <wctype.h>
#include "client.h"

void *input(void *arg) {
  int ch = 0;
  struct input_args args = *(struct input_args *)arg;
  free(arg);

  size_t max_msg_size =
      ((size_t)sysconf(_SC_PAGESIZE) - sizeof(struct chat_history)) / 3 -
      sizeof(struct chat_msg);  // Самое большое сообщение это треть страницы
                                // памяти. Почему? Просто мне так захотелось.

  char *input_buf = malloc(max_msg_size);
  if (NULL == input_buf) {
      perror("malloc");
  }
  size_t input_buf_length = 0;

  while ( ! (EOF == ch || '\x1B' == ch)) {
    // while (EOF != (ch = wgetch(args.input_window))) {  // TODO перейти
    // на wgetch, чтобы забирать управляющие клавиши, включая KEY_RESIZE.
    // Однако, с wgetch была какая-то проблема, которую я нигде не описал.
    ch = getchar();
    switch (ch) {
      case KEY_ENTER:
      case '\r':
      case '\n':
        on_key_enter(args.msg, args.input_updated, args.input_read, args.input_window, input_buf, &input_buf_length);
        break;
      case KEY_RESIZE: // не работает без wgetch
        // handle_resize(ui);
        break;
      case '\x7F':  // DEL более известный как Backspace на современных
                    // клавиатурах и терминалах
        on_key_backspace(args.input_window, input_buf, &input_buf_length);
        break;
      default:
        if (iswprint(ch) && input_buf_length < (max_msg_size - 1)) {
          waddch(args.input_window, ch);
          // Дополняем буфер сообщения для отправки
          *(input_buf + input_buf_length) = ch;
          ++input_buf_length;
          *(input_buf + input_buf_length) = '\0';
        }
    }  // switch (ch)
    wnoutrefresh(args.input_window);
    doupdate();
  }  // while (EOF != (ch = getchar()))

  if (NULL != input_buf) free(input_buf);

  send_exit_msg(args.msg, args.input_updated, args.input_read);

  return (void *)0;
}
