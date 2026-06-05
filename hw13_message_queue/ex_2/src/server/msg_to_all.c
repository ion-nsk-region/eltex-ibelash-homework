#include "mq_chat.h"

int msg_to_all(int client_mq_id, struct chat_msg msg, struct user *users,
               int n_users) {
  int err = 0;
  for (struct user *user = users + 1; user - users < n_users; ++user) {
    if (0 != (err = send_mq_msg(client_mq_id, user->pid, msg))) {
      printf(
          "Ошибка: не удалось отправить сообщение пользователю %s. "
          "См. подробности в stderr.",
          user->nickname);
    }
  }
  return err;
}
