#include "mq_chat.h"

int server_queue_handler(char *server_mq_name) {
  int err = 0, is_running = 1;
  mqd_t mq_id = 0;
  unsigned char *msg = NULL;
  pid_t client_pid, server_pid = getpid();

  err = connect2mq(server_mq_name, READ, &mq_id);
  if (0 != err || 0 >= mq_id) {
    printf("Ошибка connect2mq: %d\nСм. подробности в stderr.\n", err);
    is_running = 0;
  }
  while (is_running) {
    // читаем входящие от клиентов
    if (0 != (err = read_mq_msg(mq_id, &msg))) {
        printf("Ошибка read_mq_msg: %d\n", err);
    } 

    // switch
    //  создаём очередь для нового клиента, если её нет, 
    //  и отправляем последние 100 сообщений.

    //  обрабатываем служебные команды (подключился, отключился, завершение работы)

    //  рассылаем новое сообщение
    
  };

  return err;
}
