#include "client.h"

int handle_msg(struct chat_msg *msg, struct ui ui, struct user *users,
               int *n_users) {
  int err = 0;

  switch (msg->cmd) {
    case MSG:
      wprintw(ui.history, "[%d] %s\n", msg->sender, msg->content);
      break;
    case LIST:
      update_users_list(ui.users_list, msg->content, users, n_users);
      break;
    case HISTORY:
      // TODO
      // update_history(ui.history, msg->content, users_list);
      break;
    default:
      fprintf(stderr,
              "Предупреждение: Получено сообщение неизвестного типа %d.\n",
              msg->cmd);
      wprintw(ui.history, "[%d] %s", msg->sender, msg->content);
  }

  return err;
}
