#include "client_ui.h"

void destroy_windows(struct ui ui) {
  if (ERR == cleanup_window(ui.history) || cleanup_window(ui.users_list) ||
      cleanup_window(ui.msg_input)) {
    fprintf(stderr,
            "Ошибка: не удалось освободить память "
            "выделенную для окон.\n"
            "Рекомендуется перезапустить терминал.\n");
  }

  if (ERR == endwin()) {
    fprintf(stderr,
            "Ошибка: не удалось вернуть настройки терминала "
            "в исходное состояние.\n"
            "Рекомендуется перезапустить терминал.\n");
  }
}
