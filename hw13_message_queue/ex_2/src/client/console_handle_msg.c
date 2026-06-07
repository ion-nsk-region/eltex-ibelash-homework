#include "client.h"

void console_handle_msg(struct chat_msg *msg) {
  const char *commands[] = {"NO_COMMAND", "JOIN",    "QUIT",
                            "LIST",       "HISTORY", "MSG"};
  printf("\n\nПолучено сообщение типа %s: %s\n", commands[msg->cmd],
         msg->content);
}
