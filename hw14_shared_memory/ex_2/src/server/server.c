#include "server.h"

int main(void) {
  int err = 0;
  pthread_t server_queue_handler_tid;
  void *input_shm_addr = NULL;

  // создаём поток для обработки сообщений от клиентов
  err = pthread_create(&server_queue_handler_tid, NULL, server_queue_handler,
                       &input_shm_addr);
  if (0 != err) {
    fprintf(stderr,
            "Ошибка: не удалось создать поток для обработки входящих сообщений "
            "от клиентов:\n%s\n",
            strerror(err));
  }

  if (0 == err) {
    // завершаем работу при нажатии "q"
    wait_for_quit();

    // отправляем сообщение потоку о выходе
    server_queue_handler_exit(input_shm_addr);

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
