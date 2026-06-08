#include "client.h"

int handle_msg(struct chat_msg *msg, struct ui ui, struct user *users,
               int *n_users) {
  int err = 0;
  char *nickname = "server";
  if (1 != msg->sender) {
    nickname = pid_to_nick(users, *n_users, msg->sender);
    if (NULL == nickname) nickname = "Not found";
  }
  //  fprintf(stderr, "DEBUG: получено от %d, тип %d,\nсодержимое %s.\n",
  //          msg->sender, msg->cmd, msg->content);

  switch (msg->cmd) {
    case MSG:
      wprintw(ui.history, "%s: %s\n", nickname, msg->content);
      break;
    case LIST:
      update_users_list(ui.users_list, msg->content, users, n_users);
      break;
    case HISTORY:
      update_history_win(ui.history, msg->content, users, *n_users);
      break;
    default:
      fprintf(stderr,
              "Предупреждение: сообщение неизвестного типа\n"
              "Отправитель [%d] %s, тип %d,\n"
              "содержимое: %s.\n",
              msg->sender, nickname, msg->cmd, msg->content);
      wprintw(ui.history,
              "Предупреждение: сообщение неизвестного типа\n"
              "Отправитель [%d] %s, тип %d,\n"
              "содержимое: %s.\n",
              msg->sender, nickname, msg->cmd, msg->content);
  }

  return err;
}
