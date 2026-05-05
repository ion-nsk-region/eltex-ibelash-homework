#include "mq_chat.h"

int main(void) {
  int err = 0;
  char *mq_name = "./sysv_server.exe";
  int mq_id = 0;
  char *msg = "Hi!";
  char *reply = NULL;

  // Создаём очередь
  int mq_flags = IPC_CREAT | 0660;
  err = connect2mq(mq_name, mq_flags, &mq_id);

  // Отправляем сообщение
  if (0 == err && 0 != mq_id && (0 != send_mq_msg(mq_id, msg, sizeof(msg)))) {
    printf("Ошибка send_mq_msg: %d\n", err);
  }

  // Читаем ответ
  long unsigned int mq_num = 0;
  pid_t my_pid = getpid(), last_sender_pid;
  if (0 == err && 0 != mq_id) {
    int n_attempts = 0;
    do {
      err = get_last_sender_pid(mq_id, &last_sender_pid);
      if (0 == err)
        err = conn_timer(CONNECTION_TIMEOUT, SLEEP_TIME, n_attempts++);
    } while (last_sender_pid == my_pid && 0 == err);

      if (0 != (err = read_mq_msg(mq_id, 0, &reply))) {
        printf("Ошибка read_mq_msg: %d\n", err);
      } else {
        printf("%s\n", reply);
      }
  }

  // Удаляем очередь
  int is_empty = is_mq_empty(mq_id, &mq_num);
  if (1 == is_empty) {
    if (0 != (err = delete_mq(mq_id))) {
      printf(
          "Ошибка: не удалось удалить очередь сообщений.\n"
          "Перезагрузите компьютер для удаления вручную.\n");
    }
  } else if (0 == is_empty) {
    printf(
        "Предупреждение: Очередь не была удалена.\n"
        "Она не пуста и содержит %ld сообщений.\n"
        "Запустите клиента для прочтения сообщений или перезагрузите компьютер "
        "для удаления вручную.\n",
        mq_num);
  } else {
    printf(
        "Ошибка: Не удалось проверить состояние очереди.\n"
        "См. stderr для подробностей.\n");
  }

  // Выходим
  printf("Выходим.\n");

  return err;
}
