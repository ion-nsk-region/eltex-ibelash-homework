#include "mq_chat.h"

int handle_new_client(struct mq_msg new_client_msg) {
  int err = 0;
  mqd_t mq_id = 0;

  // создать очередь
  char mq_name[MQ_NAME_LENGTH];
  snprintf(mq_name, MQ_NAME_LENGTH, "/client%d", new_client_msg.sender_pid);

  if (0 != (err = create_mq(mq_name, WRITE, &mq_id))) {
    fprintf(stderr,
            "Ошибка: не удалось создать очередь для нового клиента. См. "
            "подробности в stderr.\n");
  } else {
    // TODO добавить очередь в массив очередей
  }

  // Достать ник
  char new_client_nickname[MAX_NICKNAME_LENGTH];
  if (0 == err) {
    if (0 != (err = get_nickname(new_client_msg.mtext, new_client_nickname))) {
      fprintf(stderr, "Ошибка: не удалось извлечь ник из сообщения: %s\n",
              new_client_msg.mtext);
    } else {
      // TODO добавить пользователя в список участников чата
      // new_client_msg.sender_pid, new_client_nickname
    }
  }

  fprintf(stderr, "DEBUG: создана очередь %d для пользователя %s\n", mq_id,
          new_client_nickname);

  // TODO отправить список участников чата

  // TODO отправить историю сообщений (последние 100)

  return err;
}
