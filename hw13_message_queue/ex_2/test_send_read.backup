#include "mq_chat.h"

int main(void) {
  struct chat_msg outgoing = {.sender = getpid(), .cmd = JOIN, .content = "My nickname"}, *incoming = NULL;
  char *mq_name = "./test_send_read.exe";
  int mq_id;

  create_mq(mq_name, &mq_id);
  printf("mq_id = %d\n", mq_id);

  send_mq_msg(mq_id, outgoing);

  read_mq_msg(mq_id, getpid(), &incoming);

  printf("Прочитано:\n pid_t = %d,\n cmd = %d,\n text = %s.\n",
         incoming->sender, incoming->cmd, incoming->content);

  free(incoming->content);
  free(incoming);
  delete_mq(mq_id);

  return 0;
}
