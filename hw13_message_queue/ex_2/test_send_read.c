#include "mq_chat.h"

int main(void) {
  struct msgbuf *buffer1, *buffer2;
  char *mq_name = "./test_send_read.exe";
  int mq_id;

  create_mq(mq_name, &mq_id);
  printf("mq_id = %d\n", mq_id);

  errno = 0;
  buffer1 = calloc(1, sizeof(struct msgbuf));
  if (NULL != buffer1) {
  buffer1->mtype = 1;
  buffer1->sender_pid = getpid();
  buffer1->mtext_size = 6;
  buffer1->mtext = calloc(buffer1->mtext_size, sizeof(char));
  strncpy(buffer1->mtext, "/quit", buffer1->mtext_size);
  } else {
    perror("malloc");
  }
  send_mq_msg(mq_id, buffer1);

  errno = 0;

  read_mq_msg(mq_id, 1, &buffer2);

  printf(
      "Прочитано:\n mtype = %ld,\n pid = %d,\n text_size = %ld,\n text = %s.\n",
       buffer2->mtype, buffer2->sender_pid, buffer2->mtext_size, buffer2->mtext);
      // buffer2.mtype, buffer2.sender_pid, buffer2.mtext_size, buffer2.mtext);

  delete_mq(mq_id);
  free_msg_buffer(buffer1);
  free_msg_buffer(buffer2);

  return 0;
}
