#include "server.h"

int handle_new_client(int client_mq_id, struct chat_msg client_msg,
                      struct user *users, int *n_users,
                      struct chat_msg *history, int last_msg_id) {
  int err = 0;

  // Достать ник
  char client_nickname[MAX_NICKNAME_LENGTH];
  size_t client_nickname_length;
  err = get_nickname(client_msg.content, client_nickname,
                     &client_nickname_length);
  // TODO добавить защиту, чтобы клиенты не могли использовать никнейм "server".

  // Добавить пользователя в список участников чата
  if (0 == err &&
      0 != (err = user_add(client_msg.sender, client_nickname,
                           client_nickname_length, users, n_users))) {
    printf(
        "Ошибка: не удалось добавить пользователя в список. "
        "См. подробности в stderr.\n");
  }

  return err;
}
