#include "mq_chat.h"

unsigned char *allocate_msg_buffer(long *msg_buffer_size) {
  long max_msg_size = 0;
  unsigned char *msg_buffer = NULL;
  int err = 0;

  if (NULL == msg_buffer_size) {
    fprintf(stderr,
            "Ошибка allocate_msg_buffer: Не указана переменная для передачи "
            "размера выделенного буфера.\n");
    err = -1;
  }
  if (0 == err && 0 >= *msg_buffer_size) {
    errno = 0;
    FILE *fp = fopen("/proc/sys/kernel/msgmax", "r");
    if (fp == NULL) {
        perror("Не удалось открыть /proc/sys/kernel/msgmax");
        err = -1;
    } else if (1 != fscanf(fp, "%ld", &max_msg_size)) {
        fprintf(stderr, "Ошибка чтения из /proc/sys/kernel/msgmax\n");
        err = -1;
    }
    fclose(fp);

    *msg_buffer_size = max_msg_size - sizeof(pid_t) - sizeof(long int);
  }

  if (0 == err && 0 < *msg_buffer_size) {
    errno = 0;
    msg_buffer = (unsigned char *)malloc(*msg_buffer_size);
    if (NULL == msg_buffer) {
      perror("malloc");
    }
  }

  return msg_buffer;
}
