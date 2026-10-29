#include <common.h>

void notify_about_update(int n_users, sem_t *data_updated, sem_t *count_reads,
                         sem_t *next_turn) {
  int err = 0, next_turn_val;
  sem_getvalue(next_turn, &next_turn_val);
  if (0 != next_turn_val) {
    fprintf(stderr,
            "Предупреждение: не все клиенты прочитали предыдущие данные.\n");
  }
  // Уведомляем всех клиентов об обновлении данных
  for (int i = 0; i < n_users; i++) {
    sem_post(data_updated);
  }
  // Клиенты подтверждают, что прочитали
  for (int i = 0; i < n_users; i++) {
    err = wait_for(count_reads);
    if (0 != err) {
      return;
    }
  }

  // Разрешаем клиентам ожидание следующего обновления
  for (int i = 0; i < n_users; i++) {
    sem_post(next_turn);
  }
}
