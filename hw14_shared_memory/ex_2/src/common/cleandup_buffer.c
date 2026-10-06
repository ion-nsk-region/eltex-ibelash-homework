#include "mq_chat.h"

// очистка буферов, которые были выделены в прерываемых потоках.
// Регистрировать с помощью pthread_cleanup_push
// В конце надо убрать с помощью pthread_cleanup_pop(0) или использовать
// по назначению с помощью pthread_cleanup_pop(1)

void cleanup_buffer(void *arg) {
  if (NULL != arg) free(arg);
}
