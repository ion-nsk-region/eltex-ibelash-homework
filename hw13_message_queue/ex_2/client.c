#include "mq_chat.h"

int main(void) {
  int err = 0;

  char *server_mq_name = SERVER_MQ_NAME;
  pid_t my_pid = getpid();

  mqd_t server_mq_id = 0;

  // подключаемся к очереди сервера
  err = connect2mq(server_mq_name, WRITE, &server_mq_id);
  if (ETIME == err) {
    printf("Ошибка: время ожидания сервера истекло.\n");
  } else if (0 != err) {
    printf("Ошибка connect2mq: %d\nСм. подробности в stderr.\n", err);
  }

  // подключаемся к чату
  if (0 == err && 0 < server_mq_id) {
    // struct mq_msg join_msg = {my_pid, 132, ":join Pablo Diego José Francisco de Paula Juan Nepomuceno María de los Remedios Cipriano de la Santísima Trinidad Ruiz y Picasso"};
    struct mq_msg join_msg = {my_pid, 280, ":join Забавно, но моё полное имя Пабло Диего Хосе Франциско де Паула Хуан Непомучено Мария де лос Ремедиос Чиприано де ла Сантисима Тринидад Руиз и Пикассо"};

    long total_msg_size =
        sizeof(pid_t) + sizeof(long int) + join_msg.mtext_size;
    char *msg_buffer =
        (char *)allocate_msg_buffer(server_mq_id, &total_msg_size);
    if (NULL != msg_buffer) {
      serialize_msg(join_msg, msg_buffer);
      if (0 != (err = send_mq_msg(server_mq_id, msg_buffer, total_msg_size))) {
        printf("Ошибка send_mq_msg: %d\n", err);
      }

      free(msg_buffer);
      msg_buffer = NULL;
    } else {
      err = -1;
    }
  }

  // отключаемся от очереди сервера
  if (0 == err && 0 != server_mq_id) {
    errno = 0;
    if (-1 == (err = mq_close(server_mq_id))) {
      perror("mq_close");
    } else
      server_mq_id = 0;
  }

  /*
    // считываем сообщение и выводим на экран
    if (0 == err && 0 != server_mq_id) {
      if (0 != (err = read_mq_msg(server_mq_id, &msg))) {
        printf("Ошибка read_mq_msg: %d\n", err);
      } else {
        printf("%s\n", msg);
        free(msg);
      }
    }


    // отвечаем серверу
    if (0 == err) {
      err = create_mq(client_mq_name, WRITE, &server_mq_id);
    }

    // Удаляем очередь
    if (0 == err && 0 < server_mq_id) {
      long int mq_n_messages = 0;
      int is_empty = 0, n_attempts = 0;
      do {
        is_empty = is_mq_empty(server_mq_id, &mq_n_messages);
      } while (0 == is_empty &&
               ETIME != (err = conn_timer(1, SLEEP_TIME, n_attempts++)));
      if (1 == is_empty) {
        errno = 0;
        if (-1 == (err = mq_close(server_mq_id))) {
          perror("mq_close");
        } else
          server_mq_id = 0;
        if (0 == err && 0 != (err = delete_mq(client_mq_name))) {
          printf(
              "Ошибка: не удалось удалить очередь сообщений.\n"
              "См. подробности в stderr.\n"
              "Перезагрузите компьютер для удаления вручную.\n");
        }
      } else if (0 == is_empty) {
        printf(
            "Предупреждение: Очередь не была удалена.\n"
            "Она не пуста и содержит %ld сообщений.\n"
            "Перезагрузите компьютер для удаления вручную.\n",
            mq_n_messages);
      } else {
        printf(
            "Ошибка: Не удалось проверить состояние очереди.\n"
            "См. подробности в stderr.\n");
      }
    }

    // выходим
    // printf("Выходим.\n");
    */
  return err;
}
