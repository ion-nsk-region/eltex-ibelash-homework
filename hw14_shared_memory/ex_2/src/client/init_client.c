#include "client.h"

int init_client(struct chat_msg **msg, sem_t **input_updated, sem_t **input_read, struct user **users, struct chat_history **history, sem_t **data_updated, sem_t **count_reads, sem_t **next_turn, struct ui *ui) {
int err = 0;

  size_t shm_size = (size_t)sysconf(_SC_PAGESIZE);

  *msg = attach_shm_segment(SHM_INPUT, shm_size, O_RDWR);
  if ((void *)-1 == *shm_addr) {
    goto err_exit;
  } else if ((void *)-2 == *shm_addr) {
    goto destroy_shm_input;
  }

  // users
  *users = attach_shm_segment(SHM_USERS, shm_size, O_RDONLY);
  if ((void *)-1 == *users) {
    goto detach_shm_input;
  } else if ((void *)-2 == *users) {
    goto destroy_shm_users;
  }
  
  // history
  *history = attach_shm_segment(SHM_HISTORY, shm_size, O_RDONLY);
  if ((void *)-1 == *history) {
    goto detach_shm_users;
  } else if ((void *)-2 == *history) {
    goto destroy_shm_history;
  }

  

  if (0 == err) err = nickname_prompt();
  if (0 == err) err = initialize_terminal();
  if (0 == err) err = create_windows(&ui);
  if (0 == err) {
    handle_resize(ui);
    print_help(ui);
    wmove(ui.msg_input, 1, 0);  // устанавливаем курсор в начало поля
    // refresh_windows(ui);
  }

  return err;

destroy_shm_history:
  destroy_shm_segment(SHM_HISTORY);

detach_shm_users:
  detach_shm_segment(*users, shm_size);
destroy_shm_users:
  destroy_shm_segment(SHM_USERS);

detach_shm_input:
  detach_shm_segment(*msg, shm_size);
destroy_shm_input:
 destroy_shm_segment(SHM_INPUT); 

err_exit:
  return err;
}
