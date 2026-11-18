
int init_client(struct chat_msg **msg, sem_t **input_updated, sem_t **input_read, struct user **users, struct chat_history **history, sem_t **data_updated, sem_t **count_reads, sem_t **next_turn, struct ui *ui) {
int err = 0;

  errno = 0;
  shm_fd = shm_open(SHM_FILENAME, flags, 0 /* Сервер должен был создать сегмент памяти, поэтому мы не указываем никаких прав */);
  if (-1 == shm_fd) {
    perror("shm_open");
    goto err_exit;
  }

  *shm_addr = attach_shm_segment(shm_fd, (size_t)page_size);
  if (MAP_FAILED == *shm_addr) {
    goto err_exit;
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
}
