#include "eltex_commander.h"

void refresh_all(WINDOW *left_panel, WINDOW *left_content, WINDOW *right_panel, WINDOW *right_content){
    wnoutrefresh(stdscr);
    wnoutrefresh(left_content);
    wnoutrefresh(left_panel);
    wnoutrefresh(right_panel);
    wnoutrefresh(right_content);
    doupdate();
}
