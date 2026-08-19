#ifndef SHM_CHAT_H
#define SHM_CHAT_H

#include <errno.h>
#include <stdio.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define PROJ_ID 1
#define SERVER_FILENAME "./sysv_server.exe"

union semun {
  int val;                  // значение для операции SETVAL
  struct semid_ds *buf;     // буфер для операций IPC_STAT и IPC_SET
  unsigned short *array;    // массив для операций GETALL, SETALL
#if defined(__linux__)
  struct seminfo *__buf;    // буфер для операции IPC_INFO (только на Linux)
#endif
};

void *attach_shm_segment(int shm_id);
void cleanup(void *shm_addr);
void destroy_semaphore(int sem4_id);
void destroy_shm_segment(int shm_id);
void detach_shm_segment(void *shm_addr);
void *init_chat(void);
void receive_msg(char **reply);
void send_msg(char *msg);

#endif  // SHM_CHAT_H
