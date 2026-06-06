#include "client.h"
#include "client_ui.h"

int handle_msg(struct chat_msg *msg, struct ui ui) {
    int err = 0;

    mvwprintw(ui.history, 3, 0, "[%d] %s", msg->sender, msg->content);

    return err;
}
