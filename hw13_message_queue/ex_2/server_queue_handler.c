#include "mq_chat.h"

void *server_queue_handler(void *server_mq_name) {
  int err = 0, is_running = 1;
  int mq_id = 0;
  char *msg_buffer = NULL;
  struct msgbuf msg = {0, 0, 0, NULL};
  pid_t server_pid = getpid();

  err = connect2mq((char *)server_mq_name, READ, &mq_id);
  if (0 != err || 0 >= mq_id) {
    printf("Ошибка connect2mq: %d\nСм. подробности в stderr.\n", err);
    is_running = 0;
  }
  while (is_running) {
    if (0 != (err = read_mq_msg(mq_id, &msg_buffer))) {
      printf("Ошибка read_mq_msg: %d\n", err);
    }

    deserialize_msg(msg_buffer, &msg);
    free(msg_buffer);
    msg_buffer = NULL;

    if (msg.sender_pid == server_pid && 0 == strncmp(":quit", msg.mtext, 6)) {
      is_running = 0;
    } else if (0 == strncmp(":join", msg.mtext, 5)) {
      handle_new_client(msg);
    } else if (0 == strncmp(":disconnected", msg.mtext, 14)) {
      // handle_disconnected_client(msg.sender_pid);
    } else {
      // push_msg_to_history(msg);
      // msg_to_all(msg);
    }

    fprintf(stderr, "DEBUG получено сообщение от %d размером %ld байт: %s\n",
            msg.sender_pid, msg.mtext_size, msg.mtext);
    free(msg.mtext);
    msg.mtext = NULL;
  };

  if (0 != mq_id) {
    errno = 0;
    if (-1 == mq_close(mq_id)) {
      perror("mq_close");
    } else {
      mq_id = 0;
      if (0 != (err = delete_mq(server_mq_name))) {
        printf(
            "Ошибка: не удалось удалить очередь сообщений для обработки"
            " сообщений от клиентов.\n"
            "См. подробности в stderr.\n"
            "Перезагрузите компьютер для удаления вручную.\n");
      }
    }
  }

  return (void *)0;
}
