#include "client_ui.h"

void destroy_windows(struct ui ui) {
  cleanup_window(ui.history);
  cleanup_window(ui.users_list);
  cleanup_window(ui.msg_input);
}
