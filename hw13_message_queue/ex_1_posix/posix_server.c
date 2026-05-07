#include "mq_chat.h"

int main(void) {
  int err = 0;
  char *server_mq_name = SERVER_MQ_NAME;
  mqd_t mq_id = 0;
  char *msg = "Hi!";
  char *reply = NULL;

  // Создаём очередь
  err = create_mq(server_mq_name, &mq_id);

  // Отправляем сообщение
  if (0 == err && 0 != mq_id && (0 != send_mq_msg(mq_id, msg, sizeof(msg)))) {
    printf("Ошибка send_mq_msg: %d\n", err);
  }

  // Удаляем очередь
  if (0 == err) {
    long int mq_n_messages = 0;
    int is_empty = 0, n_attempts = 0;
    while (0 == is_empty && ETIME != err) {
      err = conn_timer(CONNECTION_TIMEOUT, SLEEP_TIME, n_attempts++);
      is_empty = is_mq_empty(mq_id, &mq_n_messages);
    }
    if (1 == is_empty) {
      errno = 0;
      if (-1 == (err = mq_close(mq_id))) {
        perror("mq_close");
      }
      if (0 == err && 0 != (err = delete_mq(server_mq_name))) {
        printf(
            "Ошибка: не удалось удалить очередь сообщений.\n"
            "Перезагрузите компьютер для удаления вручную.\n");
      }
    } else if (0 == is_empty) {
      printf(
          "Предупреждение: Очередь не была удалена.\n"
          "Она не пуста и содержит %ld сообщений.\n"
          "Запустите клиента для прочтения сообщений или перезагрузите "
          "компьютер для удаления вручную.\n",
          mq_n_messages);
    } else {
      printf(
          "Ошибка: Не удалось проверить состояние очереди.\n"
          "См. stderr для подробностей.\n");
    }
  }

  // Читаем ответ
  if (0 == err && 0 != mq_id) {
    char *client_mq_name = CLIENT_MQ_NAME;
    err = connect2mq(client_mq_name, &mq_id);
    if (ETIME == err) {
      printf("Ошибка: время ожидания ответа от клиента истекло.\n");
    } else if (0 != err) {
      printf("Ошибка connect2mq: %d\nСм. подробности в stderr.\n", err);
    }
    if (0 != (err = read_mq_msg(mq_id, &reply))) {
      printf("Ошибка read_mq_msg: %d\n", err);
    } else {
      printf("%s\n", reply);
      free(reply);
      reply = NULL;
    }
  }

  // отключаемся от очереди клиента
  if (0 == err && 0 != mq_id) {
    errno = 0;
    if (-1 == (err = mq_close(mq_id))) {
      perror("mq_close");
    }
  }

  // Выходим
  printf("Выходим.\n");

  return err;
}
