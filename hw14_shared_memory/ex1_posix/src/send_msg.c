#include "shm_chat.h"

int send_msg(void *shm_addr, const char *msg) {
  int err = 0;

  if (NULL == shm_addr || NULL == msg) {
    err = -1;
  }

  if (0 == err) {
    struct shm_msg *buf = shm_addr;
    buf->msize = strlen(msg);
    strncpy(buf->mdata, msg, buf->msize);
  }

  return err;
}
