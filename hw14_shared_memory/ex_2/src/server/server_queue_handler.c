#include "server.h"

void *server_queue_handler(void **input_shm_addr) {
  int err = 0, is_running = 1, n_users = 0;
  struct chat_msg *msg = NULL;
  struct chat_msg *history = NULL;
  struct user *users = NULL;
  pid_t server_pid = getpid();
  sem_t *data_updated, *count_reads;

  err =
      init_chat(input_shm_addr, &data_updated, &count_reads, &users, &history);

  if (0 != err) is_running = 0;

  while (is_running) {
    err = receive_msg(*input_shm_addr, &msg) if (0 != err) {
      printf("Ошибка receive_msg: %d\n", err);
    }

    switch (msg->cmd) {
      case QUIT:
        if (msg->sender == server_pid) {
          is_running = 0;
        } else {
          handle_disconnected_client(msg->sender, users, &n_users);
        }
        break;
      case JOIN:
        handle_new_client(*msg, users, &n_users);
        break;
      default:
        printf("Получена неизвестная команда с кодом %d.\n", msg->cmd);
    }

    history_update(msg, history);
    notify_about_update(&data_updated, n_users, &count_reads);
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
  err = server_cleanup(input_shm_addr, data_updated, count_reads, users, n_users, history);

  return (void *)(intptr_t)err;
}
