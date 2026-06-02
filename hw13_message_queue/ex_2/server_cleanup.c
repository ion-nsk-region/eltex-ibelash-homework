#include "mq_chat.h"

int server_cleanup(int server_mq_id, int client_mq_id) {
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
  return err;
}
