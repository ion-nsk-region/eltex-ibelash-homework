#include "mq_chat.h"

void deserialize_msg(const char *mdata, size_t mdata_size, struct chat_msg *msg) {
  size_t offset = 0;
  
  memcpy(&msg->sender, mdata + offset, sizeof(pid_t));
  offset += sizeof(pid_t);
  
  memcpy(&msg->cmd, mdata + offset, sizeof(enum chat_command));
  offset += sizeof(enum chat_command);

  // вычисляем размер текстовой части и выделяем для неё память
  size_t content_size = mdata_size - offset;
  if (0 < content_size) {
  errno = 0;
  msg->content = malloc(content_size * sizeof(char));
  if (NULL == msg->content) {
    perror("malloc");
  } else {
    memcpy(msg->content, mdata + offset, content_size);
  }
  } else {
    // обрабатываем ситуацию, когда текстовая часть сообщения отсутствует
    msg->content = NULL;
    // Имеет ли смысл вставлять какой-то плейсхолдер (например "Empty")?
  }
}
