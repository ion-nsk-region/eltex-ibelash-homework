#include "mq_chat.h"

int server_cleanup(int server_mq_id, int client_mq_id, struct user *users, int n_users, struct chat_msg *history) {
  int err = 0;
  if (-1 < server_mq_id) {
    if (0 != (err = delete_mq(server_mq_id))) {
      printf(
          "Ошибка: не удалось удалить очередь для обработки"
          " сообщений от клиентов.\nСм. подробности в stderr.\n"
          "Перезагрузите компьютер для удаления вручную.\n");
    }
  }
  if (-1 < client_mq_id) {
    if (0 != (err = delete_mq(client_mq_id))) {
      printf(
          "Ошибка: не удалось удалить очередь для исходящих"
          " сообщений для клиентов.\nСм. подробности в stderr.\n"
          "Перезагрузите компьютер для удаления вручную.\n");
    }
  }
  if (NULL != users && 0 < n_users) {
    for (struct user *user = users; user - users < n_users; ++user) {
      free(user->nickname);
    }
    free(users);
  }
  for (struct chat_msg *msg = history; msg - history < MAX_HISTORY_SIZE; ++msg){
   if (NULL != msg->content) free(msg->content);
  }
  return err;
}
