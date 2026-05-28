#include "mq_chat.h"

int server_queue_handler_exit(int server_mq_id) {
  int err = 0;
  struct msgbuf msg;
  msg.mtype = 1;
  msg.sender_pid = getpid();
  msg.mtext_size = sizeof(":quit");
  msg.mtext = ":quit";
  long total_msg_size = sizeof(long) + sizeof(pid_t) + sizeof(long int) + msg.mtext_size;

  char *msg_buffer = (char *)allocate_msg_buffer(server_mq_id, &total_msg_size);
  if (NULL != msg_buffer) {
    serialize_msg(msg, msg_buffer);
    if(0 != (err = send_mq_msg(server_mq_id, msg_buffer, total_msg_size))) {
        printf("Ошибка: не удалось отправить сообщение потоку о выходе. См. подробности в stderr.\n");
    }

    free(msg_buffer);
    msg_buffer = NULL;
  } else {
    err = -1;
  }

  return err;
}
