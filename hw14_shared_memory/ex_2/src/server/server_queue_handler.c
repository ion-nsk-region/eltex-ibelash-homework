#include "server.h"

void *server_queue_handler(void *input_shm_addr) {
  int err = 0, is_running = 1, n_users = 0;
  struct chat_msg *msg = NULL;
  struct chat_msg *history = NULL;
  struct user *users = NULL;
  pid_t server_pid = getpid();
  sem_t *data_updated, *count_reads, *next_turn, *input_updated, *input_read;

  err = init_chat(&input_shm_addr, &input_updated, &input_read, &users, &history,
                  &data_updated, &count_reads, &next_turn);

  if (0 != err) is_running = 0;
  msg = input_shm_addr;

  while (is_running) {
    wait_for(input_updated);

    switch (msg->cmd) {
      case MSG:
        break;
      case QUIT:
        if (msg->sender == server_pid) {
          is_running = 0;
        } else {
          handle_disconnected_client(msg->sender, users, &n_users);
        }
        break;
      case JOIN:
        handle_new_client(msg, users, &n_users);
        break;
      default:
        printf("Получена неизвестная команда с кодом %d.\n", msg->cmd);
    }

    history_update(msg, history, input_read);
    notify_about_update(n_users, data_updated, count_reads, next_turn);
    /*
    // при изменении массива "commands" также необходимо изменить "enum
    // chat_command" в заголовочном файле.
    const char *commands[] = {"NO_COMMAND", "JOIN",    "QUIT",
                              "LIST",       "HISTORY", "MSG"};
    fprintf(stderr, "DEBUG получено сообщение от %d с командой %s: %s\n",
            msg->sender, commands[msg->cmd], msg->content);
    */
  };  // while (is_running)

  // очищаем выделенные ресурсы
  msg = NULL;
  err = server_cleanup(input_shm_addr, input_updated, input_read, users,
                       history, data_updated, count_reads, next_turn);

  return (void *)(intptr_t)err;
}
