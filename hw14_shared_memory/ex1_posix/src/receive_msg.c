#include <stdlib.h>

#include "shm_chat.h"

int receive_msg(void *shm_addr, char **msg) {
  int err = 0;

  if (NULL == shm_addr || NULL == msg) {
    err = -1;
  }

  if (0 == err) {
    const struct shm_msg *buf = shm_addr;
    *msg = (char *)malloc(sizeof(char) * (buf->msize + 1));
    if (NULL == *msg) {
      err = errno;
      perror("malloc");
    } else {
      char *end = stpncpy(*msg, buf->mdata, buf->msize);
      *end = '\0';
    }
  }

  return err;
}
