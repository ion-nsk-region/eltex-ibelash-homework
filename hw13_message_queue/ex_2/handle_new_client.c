#include "mq_chat.h"

int handle_new_client(struct chat_msg new_client_msg) {
  int err = 0;

  // Достать ник
  char new_client_nickname[MAX_NICKNAME_LENGTH];
  err = get_nickname(new_client_msg.content, new_client_nickname);

  printf("DEBUG Подключается пользователь %s.\n", new_client_nickname);

  // TODO добавить пользователя в список участников чата
  // new_client_msg.sender, new_client_nickname

  // TODO отправить список участников чата

  // TODO отправить историю сообщений (последние 100)

  // TODO уведомить других участников о новом пошьзователе

  return err;
}
