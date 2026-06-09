#include "client.h"

void client_cleanup(pthread_t reader_tid, pthread_t input_tid,
                    pthread_mutex_t *refresh_lock, pthread_cond_t *refresh_cond,
                    struct ui ui, struct user *users, int n_users) {
  close_threads(reader_tid, input_tid);
  pthread_mutex_destroy(refresh_lock);
  pthread_cond_destroy(refresh_cond);
  destroy_windows(ui);

  for (struct user *user = users; user - users < n_users; ++user) {
    if (NULL != user->nickname) free(user->nickname);
  }
}
