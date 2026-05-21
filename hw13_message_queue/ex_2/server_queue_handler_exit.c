#include "mq_chat.h"

int server_queue_handler_exit(mqd_t server_mq_id) {
  int err = 0;
  struct mq_msg msg;
  msg.sender_pid = getpid();
  msg.mtext_size = sizeof("/quit");
  msg.mtext = "/quit";
  long total_msg_size = sizeof(pid_t) + sizeof(long int) + msg.mtext_size;

  char *msg_buffer = (char *)allocate_msg_buffer(server_mq_id, &total_msg_size);
  if (NULL != msg_buffer) {
    serialize_msg(msg, msg_buffer);
    err = send_mq_msg(server_mq_id, msg_buffer, total_msg_size);

    free(msg_buffer);
    msg_buffer = NULL;
  } else {
    err = -1;
  }

  return err;
}
