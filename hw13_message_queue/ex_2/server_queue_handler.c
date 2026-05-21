#include "mq_chat.h"

void *server_queue_handler(void *server_mq_name) {
  int err = 0, is_running = 1;
  mqd_t mq_id = 0;
  char *msg_buffer = NULL;
  struct mq_msg msg = {0, 0, NULL};
  pid_t server_pid = getpid();

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

    deserialize_msg(msg_buffer, &msg);
    free(msg_buffer);
    if (msg.sender_pid == server_pid && 0 == strncmp("/quit", msg.mtext, 6)) {
        is_running = 0;
    }
    fprintf(stderr, "DEBUG получено сообщение от %d размером %ld байт: %s\n%p\n", msg.sender_pid, msg.mtext_size, msg.mtext, msg.mtext);
    free(msg.mtext);

    // switch
    //  создаём очередь для нового клиента, если её нет, 
    //  и отправляем последние 100 сообщений.

    //  обрабатываем служебные команды (подключился, отключился, завершение работы)

    //  рассылаем новое сообщение
    
  };
  return (void *)0;
}
