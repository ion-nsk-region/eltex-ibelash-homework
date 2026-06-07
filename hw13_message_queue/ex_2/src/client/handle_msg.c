#include "client.h"
#include "client_ui.h"

int handle_msg(struct chat_msg *msg, struct ui ui) {
  int err = 0;

  switch(msg->cmd) {
    case MSG:
            wprintw(ui.history, "[%d] %s\n", msg->sender, msg->content);
            break;
    case LIST:
           // TODO
           // update_users_list();
            break;
    case HISTORY:
            // TODO
            // update_history();
            break;
    default:
            fprintf(stderr, "Предупреждение: Получено сообщение неизвестного типа %d.\n", msg->cmd);
            wprintw(ui.history, "[%d] %s", msg->sender, msg->content);


  }

  return err;
}
