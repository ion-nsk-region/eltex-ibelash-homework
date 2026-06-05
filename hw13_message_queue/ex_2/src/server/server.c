#include "mq_chat.h"

int main(void) {
  int err = 0;
  char *server_mq_name = SERVER_MQ_NAME;
  int server_mq_id = -1, client_mq_id = -1;
  pthread_t server_queue_handler_tid;

  // очередь для чтения входящих сообщений от клиентов и общения с самим собой
  if (0 != (err = create_mq(server_mq_name, &server_mq_id))) {
    fprintf(stderr,
            "Ошибка: не удалось создать очередь для обработки "
            "сообщений от клиентов. См. подробности в stderr.\n");
  }
  // очередь для исходящих сообщений для клиентов
  if (0 != (err = create_mq(CLIENT_MQ_NAME, &client_mq_id))) {
    fprintf(stderr,
            "Ошибка: не удалось создать очередь для исходящих "
            "сообщений для клиентов. См. подробности в stderr.\n");
  }

  // создаём поток для обработки сообщений от клиентов
  if (0 == err &&
      0 != (err = pthread_create(&server_queue_handler_tid, NULL,
                                 server_queue_handler, server_mq_name))) {
    fprintf(stderr,
            "Ошибка: не удалось создать поток для обработки входящих сообщений "
            "от клиентов:\n%s\n",
            strerror(err));
  }

  if (0 == err) {
    // завершаем работу при нажатии "q"
    wait_for_quit();

    // отправляем сообщение потоку о выходе
    server_queue_handler_exit(server_mq_id);

    void *status;
    if (0 == (err = pthread_join(server_queue_handler_tid, &status))) {
      int exit_code = (int)(intptr_t)status;
      if (0 != exit_code) {
        printf(
            "Поток обработки входящих сообщений от клиентов завершился со "
            "статусом %d\n",
            exit_code);
      }
    } else {
      fprintf(stderr, "pthread_join: %s\n", strerror(err));
    }
  }

  return err;
}
