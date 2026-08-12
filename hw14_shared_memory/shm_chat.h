#ifndef SHM_CHAT_H
#define SHM_CHAT_H

#include <stdio.h>
#include <sys/sem.h>
#include <sys/shm.h>

#define PROJ_ID 1
#define SERVER_FILENAME "./sysv_server.exe"

void cleanup(void *shm_addr);
int  init_chat(void **shm_addr);
void receive_msg(char **reply);
void send_msg(char *msg);

#endif // SHM_CHAT_H
