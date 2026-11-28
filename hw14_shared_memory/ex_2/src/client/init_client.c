#include "client.h"

int init_client(struct chat_msg **msg, sem_t **input_updated,
                sem_t **input_read, struct user **users,
                struct chat_history **history, sem_t **data_updated,
                sem_t **count_reads, sem_t **next_turn, struct ui *ui) {
  int err = 0;

  size_t shm_size = (size_t)sysconf(_SC_PAGESIZE);

  // input
  *msg = (struct chat_msg *)attach_shm_segment(SHM_INPUT, shm_size, O_RDWR);
  if (NULL == *msg) {
    printf("Предупреждение: не могу подключиться к разделяемой памяти. Проверьте что сервер запущен.\n");      
    goto err_exit;
  } else if ((void *)-1 == *msg) {
    goto err_exit;
  } else if ((void *)-2 == *msg) {
    goto detach_shm_input;
  }

  // users
  *users = (struct user *)attach_shm_segment(SHM_USERS, shm_size, O_RDONLY);
  if ((void *)-1 == *users) {
    goto detach_shm_input;
  } else if ((void *)-2 == *users) {
    goto detach_shm_users;
  }

  // history
  *history = (struct chat_history *)attach_shm_segment(SHM_HISTORY, shm_size, O_RDONLY);
  if ((void *)-1 == *history) {
    goto detach_shm_users;
  } else if ((void *)-2 == *history) {
    goto detach_shm_history;
  }

  // Семафоры
  errno = 0;
  *input_updated = sem_open(SEM4_INPUT_UPDATED, 0);
  if (SEM_FAILED == *input_updated) {
    perror("sem_open");
    goto detach_shm_history;
  }

  errno = 0;
  *input_read = sem_open(SEM4_INPUT_READ, 0);
  if (SEM_FAILED == *input_read) {
    perror("sem_open");
    goto close_input_updated;
  }

  errno = 0;
  *data_updated = sem_open(SEM4_DATA_UPDATED, 0);
  if (SEM_FAILED == *data_updated) {
    perror("sem_open");
    goto close_input_read;
  }

  errno = 0;
  *count_reads = sem_open(SEM4_COUNT_READS, 0);
  if (SEM_FAILED == *count_reads) {
    perror("sem_open");
    goto close_data_updated;
  }

  errno = 0;
  *next_turn = sem_open(SEM4_NEXT_TURN, 0);
  if (SEM_FAILED == *next_turn) {
    perror("sem_open");
    goto close_count_reads;
  }

  if (0 == err) err = join_chat(*msg, *input_updated, *input_read);
  if (0 == err) err = initialize_terminal();
  if (0 == err) err = create_windows(ui);
  if (0 == err) {
    handle_resize(*ui);
    print_help(*ui);
    wmove(ui->msg_input, 1, 0);  // устанавливаем курсор в начало поля
  }

  return err;

  // очистка ресурсов в случае ошибки

close_count_reads:
  close_semaphore(*count_reads);

close_data_updated:
  close_semaphore(*data_updated);

close_input_read:
  close_semaphore(*input_read);

close_input_updated:
  close_semaphore(*input_updated);

detach_shm_history:
  detach_shm_segment(*history, shm_size);

detach_shm_users:
  detach_shm_segment(*users, shm_size);

detach_shm_input:
  detach_shm_segment(*msg, shm_size);

err_exit:
  return -1;
}
