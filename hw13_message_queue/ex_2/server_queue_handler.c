#include "mq_chat.h"

void *server_queue_handler(void *server_mq_name) {
  int err = 0, is_running = 1;
  mqd_t mq_id = 0;
  char *msg_buffer = NULL;
  struct mq_msg msg;
  // pid_t client_pid, server_pid = getpid();

  err = connect2mq((char *)server_mq_name, READ, &mq_id);
  if (0 != err || 0 >= mq_id) {
    printf("Ошибка connect2mq: %d\nСм. подробности в stderr.\n", err);
    is_running = 0;
  }
  while (is_running) {
    // читаем входящие от клиентов
    if (0 != (err = read_mq_msg(mq_id, &msg_buffer))) {
        printf("Ошибка read_mq_msg: %d\n", err);
    } 

    // десериализация
    size_t offset = 0;
    memcpy(&msg.sender_pid, msg_buffer + offset, sizeof(pid_t));
    offset += sizeof(pid_t);
    memcpy(&msg.mtext_size, msg_buffer + offset, sizeof(long int));
    offset += sizeof(long int);
    errno = 0;
    msg.mtext = malloc(msg.mtext_size);
    if (NULL == msg.mtext) {
        perror("malloc");
        err = -1;
    } else {
        memcpy(&msg.mtext, msg_buffer + offset, msg.mtext_size);
    }

    fprintf(stderr, "DEBUG получено сообщение от %d размером %ld байт: %s\n", msg.sender_pid, msg.mtext_size, msg.mtext);

    // switch
    //  создаём очередь для нового клиента, если её нет, 
    //  и отправляем последние 100 сообщений.

    //  обрабатываем служебные команды (подключился, отключился, завершение работы)

    //  рассылаем новое сообщение
    
  };
  return (void *)0;
}
