#ifndef CLIENT_UI_H
#define CLIENT_UI_H

#include <curses.h>
#include "mq_chat.h"

#define MIN_MSG_INPUT_HEIGHT 3 // Минимальная высота поля (в строках) для ввода текста с учётом рамки сверху. То есть эффективная высота на одну строку меньше.
#define REL_MSG_INPUT_HEIGHT 15 // Высота поля для ввода текста в процентах относительно высоты главного окна/терминала
#define REL_HISTORY_WIDTH 70 // Ширина окна с историей чата в процентах относительно ширины главного окна/терминала

struct ui {
    WINDOW *history;
    WINDOW *users_list;
    WINDOW *msg_input;
};

int cleanup_window(WINDOW *win);
int create_windows(struct ui *ui);
void destroy_windows(struct ui ui);
int initialize_terminal(void);
int init_colors(void);
int handle_msg(struct chat_msg *msg, struct ui ui);
void handle_resize(struct ui ui);
void print_help(struct ui ui);
void refresh_windows(struct ui ui);

#endif // CLIENT_UI_H
