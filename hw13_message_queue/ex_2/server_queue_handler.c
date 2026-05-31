#include "mq_chat.h"

void *server_queue_handler(void *server_mq_name) {
  int err = 0, is_running = 1;
  int mq_id = -1;
  struct chat_msg *msg = NULL;
  pid_t server_pid = getpid();

  err = connect2mq((char *)server_mq_name, &mq_id);
  if (0 != err || 0 > mq_id) {
    printf("Ошибка connect2mq: %d\nСм. подробности в stderr.\n", err);
    is_running = 0;
  }
  while (is_running) {
    if (0 != (err = read_mq_msg(mq_id, 0, &msg))) {
      printf("Ошибка read_mq_msg: %d\n", err);
    }

    switch (msg->cmd) {
      case QUIT:
        if (msg->sender == server_pid) is_running = 0;
        break;
      case JOIN:
        handle_new_client(*msg);
        break;
      case DISCONNECTED:
        // handle_disconnected_client(msg.sender_pid);
        break;
      case MSG:
        // push_msg_to_history(msg);
        // msg_to_all(msg);
        break;
      default:
        printf("Получена неизвестная команда с кодом %d.\n", msg->cmd);
    }

    const char *commands[] = {"JOIN", "QUIT", "DISCONNECTED", "MSG"};
    fprintf(stderr, "DEBUG получено сообщение от %d с командой %s: %s\n",
            msg->sender, commands[msg->cmd], msg->content);
    free(msg->content);
    free(msg);
    msg = NULL;
  }; // while (is_running)

  if (-1 < mq_id) {
    if (0 != (err = delete_mq(mq_id))) {
      printf(
          "Ошибка: не удалось удалить очередь для обработки"
          " сообщений от клиентов.\n"
          "См. подробности в stderr.\n"
          "Перезагрузите компьютер для удаления вручную.\n");
    }
  }

  return (void *)(intptr_t)err;
}
