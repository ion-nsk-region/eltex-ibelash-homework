#include "mq_chat.h"

int main(void) {
  int err = 0;
  char *server_mq_name = SERVER_MQ_NAME;
  int mq_id = 0;
  pthread_t server_queue_handler_tid;

  // очередь для чтения входящих сообщений от клиентов и общения с самим собой
  if (0 != (err = create_mq(server_mq_name, READ_WRITE, &mq_id))) {
    fprintf(stderr,
            "Ошибка: не удалось создать очередь сообщений для обработки"
            "сообщений от клиентов. См. подробности в stderr.\n");
  }

  // создаём поток для обработки сообщений от клиентов
  if (0 != (err = pthread_create(&server_queue_handler_tid, NULL,
                                 server_queue_handler, server_mq_name))) {
    fprintf(stderr,
            "Ошибка: не удалось создать поток для обработки входящих сообщений "
            "от клиентов:\n%s\n",
            strerror(err));
  }

  // завершаем работу при нажатии "q"
  wait_for_quit();

  // отправляем сообщение потоку о выходе
  server_queue_handler_exit(mq_id);

  void *status;
  if (0 == (err = pthread_join(server_queue_handler_tid, &status))) {
    long int exit_code = (long int)status;
    if (0 != exit_code) {
      printf(
          "Поток обработки входящих сообщений от клиентов завершился со "
          "статусом %ld\n",
          exit_code);
    }
  } else {
    fprintf(stderr, "pthread_join: %s\n", strerror(err));
  }

  // очищаем выделенные ресурсы
  /*
  if (0 == err) {
    server_cleanup();
  }
*/

  // Выходим
  //  printf("Выходим.\n");

  return err;
}
