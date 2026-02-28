#ifndef ELTEX_COMMANDER_H
#define ELTEX_COMMANDER_H

#include <curses.h>
#include <stdio.h>

int cleanup(WINDOW *left_panel, WINDOW *right_panel);
int create_panels(WINDOW *stdscr, WINDOW **left_panel, WINDOW **right_panel); 
int initialize_terminal(void);
void resize_panels(WINDOW *left_panel, WINDOW *right_panel); 

#endif // ELTEX_COMMANDER_H
