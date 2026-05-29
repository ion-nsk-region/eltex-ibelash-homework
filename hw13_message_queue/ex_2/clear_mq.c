#include "mq_chat.h"

int clear_mq(char *mq_name) {
  int err = 0;
  int mq_id;
  long msg_size = 0;
  char *msg_buf = NULL;

  if (0 != (err = connect2mq(mq_name, &mq_id))) {
    printf("Ошибка connect2mq. Не удалось подключиться к очереди %s. См. подробности в stderr.", mq_name);
  }

 
  if (0 == err && -1 != mq_id) {
    msg_buf = (char *)allocate_msg_buffer(&msg_size);
    if (NULL == msg_buf) {
      printf(
          "Не удалось выделить память под буфер чтения сообщений."
          " См. подробности в stderr.\n");
      err = -1;
    }
  }
 
  if (0 == err && -1 != mq_id) {
    int msg_flags = IPC_NOWAIT | MSG_NOERROR;
    while (0 == is_mq_empty(mq_id, NULL) && 0 == err) {
      errno = 0;
      if (-1 == msgrcv(mq_id, &msg_buf, msg_size, 0, msg_flags) && ENOMSG != errno) {
        perror("msgrcv");
        err = -1;
      }
    }
  }

  if (NULL != msg_buf) free(msg_buf);

  return err;
}
