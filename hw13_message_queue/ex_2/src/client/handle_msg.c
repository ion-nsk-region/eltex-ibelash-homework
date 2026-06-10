#include "client.h"

int handle_msg(struct chat_msg *msg, struct ui ui, struct user *users,
               int *n_users) {
  int err = 0, free_nick = 0;
  char *nickname = pid_to_nick(users, *n_users, msg->sender, &free_nick);

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

  if (free_nick) free(nickname);

  return err;
}
