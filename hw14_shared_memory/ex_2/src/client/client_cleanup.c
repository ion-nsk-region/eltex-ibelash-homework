#include "client.h"

void client_cleanup(pthread_t reader_tid, pthread_t input_tid,
                    pthread_mutex_t *refresh_lock, pthread_cond_t *refresh_cond,
                    pthread_mutex_t *msg_processing_lock,
                    pthread_cond_t *msg_processing_cond,
                    pthread_mutex_t *ch_processing_lock,
                    pthread_cond_t *ch_processing_cond, struct user *users,
                    int n_users) {
  close_threads(reader_tid, input_tid);
  pthread_mutex_destroy(refresh_lock);
  pthread_cond_destroy(refresh_cond);
  pthread_mutex_destroy(msg_processing_lock);
  pthread_cond_destroy(msg_processing_cond);
  pthread_mutex_destroy(ch_processing_lock);
  pthread_cond_destroy(ch_processing_cond);

  for (struct user *user = users; user - users < n_users; ++user) {
    if (NULL != user->nickname) free(user->nickname);
  }
}
