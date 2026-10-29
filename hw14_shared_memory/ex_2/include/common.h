#ifndef COMMON_H
#define COMMON_H

#include "shm_chat.h"

void *attach_shm_segment(int shm_fd, size_t shm_size);
int close_semaphore(sem_t *sem4_id);
void destroy_semaphore(sem_t *sem4_id, const char *sem4_name);
void destroy_shm_segment(const char *shm_name);
void detach_shm_segment(void *shm_addr, size_t page_size);
int send_msg(struct chat_msg *shm_addr, struct chat_msg msg, sem_t *sem4_input_updated, sem_t *sem4_input_read);
int wait_for(sem_t *sem4_id);

#endif // COMMON_H
