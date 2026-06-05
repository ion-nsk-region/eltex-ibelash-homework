#include "mq_chat.h"

void *server_queue_handler(void *server_mq_name) {
  int err = 0, is_running = 1, n_users = 0;
  int server_mq_id = -1, client_mq_id = -1;
  struct chat_msg *msg = NULL;
  struct chat_msg history[MAX_HISTORY_SIZE] = {};
  int last_msg_id = MAX_HISTORY_SIZE - 1;
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
      err = user_add(server_pid, "server", 6, users, &n_users);
    }
  }

  if (0 != err) is_running = 0;

  while (is_running) {
    if (0 != (err = read_mq_msg(server_mq_id, 0, &msg))) {
      printf("Ошибка read_mq_msg: %d\n", err);
    } else {
      history_update(*msg, history, &last_msg_id);
    }

    switch (msg->cmd) {
      case QUIT:
        if (msg->sender == server_pid)
          is_running = 0;
        else {  // handle_disconnected_client();
        }
        break;
      case JOIN:
        handle_new_client(client_mq_id, *msg, users, &n_users, history,
                          last_msg_id);
        break;
      case MSG:
        msg_to_all(client_mq_id, *msg, users, n_users);
        break;
      default:
        printf("Получена неизвестная команда с кодом %d.\n", msg->cmd);
    }

    // при изменении массива "commands" также необходимо изменить "enum
    // chat_command" в заголовочном файле.
    const char *commands[] = {"NO_COMMAND", "JOIN",    "QUIT",
                              "LIST",       "HISTORY", "MSG"};
    fprintf(stderr, "DEBUG получено сообщение от %d с командой %s: %s\n",
            msg->sender, commands[msg->cmd], msg->content);
    free(msg);
    msg = NULL;
  };  // while (is_running)

  // очищаем выделенные ресурсы
  err = server_cleanup(server_mq_id, client_mq_id, users, n_users, history);

  return (void *)(intptr_t)err;
}
