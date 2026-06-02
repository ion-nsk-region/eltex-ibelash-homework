#include "mq_chat.h"

void *server_queue_handler(void *server_mq_name) {
  int err = 0, is_running = 1, n_users = 0;
  int server_mq_id = -1, client_mq_id = -1;
  struct chat_msg *msg = NULL;
  struct user *users = NULL;
  pid_t server_pid = getpid();

  err = connect2mq((char *)server_mq_name, &server_mq_id);
  if (0 != err || 0 > server_mq_id) {
    printf("Ошибка connect2mq: %d\nСм. подробности в stderr.\n", err);
    is_running = 0;
  }

  err = connect2mq(CLIENT_MQ_NAME, &client_mq_id);
  if (0 != err || 0 > client_mq_id) {
    printf("Ошибка connect2mq: %d\nСм. подробности в stderr.\n", err);
    is_running = 0;
  }

  // создаём список пользователей
  if (0 == err) {
    errno = 0;
    users = malloc(MAX_CHAT_USERS * sizeof(struct user));
    if (NULL == users) {
      err = errno;
      perror("malloc");
      is_running = 0;
    } else {
      user_add(server_pid, "server", 6, users, &n_users);
    }
  }

  while (is_running) {
    if (0 != (err = read_mq_msg(server_mq_id, 0, &msg))) {
      printf("Ошибка read_mq_msg: %d\n", err);
    }

    switch (msg->cmd) {
      case QUIT:
        if (msg->sender == server_pid) is_running = 0;
        break;
      case JOIN:
        handle_new_client(client_mq_id, *msg, users, &n_users);
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
  };  // while (is_running)


  // очищаем выделенные ресурсы
    err = server_cleanup(server_mq_id, client_mq_id);

//  return (void *)(intptr_t)err;
    return (void *)0;
}
