#include "server.h"

void *server_queue_handler(void *input_shm_addr) {
  int err = 0, is_running = 1, n_users = 0;
  struct chat_msg *history = NULL;
  int last_msg_id = MAX_HISTORY_SIZE - 1;
  struct user *users = NULL;
  pid_t server_pid = getpid();
  sem_t *data_updated, *count_reads;

  err = init_chat(&input_shm_addr, &data_updated, &count_reads, &users, &history);

  if (0 != err) is_running = 0;

  while (is_running) {
	  err = receive_msg(&input_shm_addr, )
    if (0 != (err = read_mq_msg(server_mq_id, 0, &msg))) {
      printf("Ошибка read_mq_msg: %d\n", err);
    } else {
      history_update(*msg, history, &last_msg_id);
    }

    switch (msg->cmd) {
      case QUIT:
        if (msg->sender == server_pid) {
          clear_mq(CLIENT_MQ_NAME);
          struct chat_msg msg_quit = {server_pid, QUIT, NULL};
          msg_to_all(client_mq_id, msg_quit, users, n_users);

          is_running = 0;
        } else {
          handle_disconnected_client(client_mq_id, msg->sender, users,
                                     &n_users);
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
    /*
    // при изменении массива "commands" также необходимо изменить "enum
    // chat_command" в заголовочном файле.
    const char *commands[] = {"NO_COMMAND", "JOIN",    "QUIT",
                              "LIST",       "HISTORY", "MSG"};
    fprintf(stderr, "DEBUG получено сообщение от %d с командой %s: %s\n",
            msg->sender, commands[msg->cmd], msg->content);
    */
    free(msg);
    msg = NULL;
  };  // while (is_running)

  // очищаем выделенные ресурсы
  err = server_cleanup(server_mq_id, client_mq_id, users, n_users, history);

  return (void *)(intptr_t)err;
}
