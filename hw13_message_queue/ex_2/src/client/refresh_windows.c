#include "client_ui.h"

void refresh_windows(struct ui ui) {
    wnoutrefresh(stdscr);
    wnoutrefresh(ui.history);
    wnoutrefresh(ui.users_list);
    wnoutrefresh(ui.msg_input);
    doupdate();
}
