#include "mq_chat.h"

long get_max_msg_size(void) {
  long max_msg_size = 0;

  errno = 0;
  FILE *fp = fopen("/proc/sys/kernel/msgmax", "r");
  if (fp == NULL) {
    perror("Не удалось открыть /proc/sys/kernel/msgmax");
  } else if (1 != fscanf(fp, "%ld", &max_msg_size)) {
    fprintf(stderr, "Ошибка чтения из /proc/sys/kernel/msgmax\n");
  }
  fclose(fp);

  return max_msg_size;
}
