#include "server.h"

int main(void) {
  int err = 0;
  pthread_t server_queue_handler_tid;

  err = init_chat();

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
