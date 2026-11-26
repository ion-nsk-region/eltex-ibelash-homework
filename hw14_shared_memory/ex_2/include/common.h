#ifndef COMMON_H
#define COMMON_H

#include "shm_chat.h"

void *attach_shm_segment(const char *shm_name, size_t shm_size, int shm_flags);
int close_semaphore(sem_t *sem4_id);
void destroy_semaphore(sem_t *sem4_id, const char *sem4_name);
void destroy_shm_segment(const char *shm_name);
void detach_shm_segment(void *shm_addr, size_t shm_size);
size_t get_msg_size(struct chat_history *history, size_t msg_offset);
int is_message(struct chat_history *history, size_t msg_offset);
int send_exit_msg(struct chat_msg *input, sem_t *input_updated,
                  sem_t *input_read);
int send_msg(struct chat_msg *shm_addr, struct chat_msg *msg, sem_t *sem4_input_updated, sem_t *sem4_input_read);
int wait_for(sem_t *sem4_id);

#endif // COMMON_H
