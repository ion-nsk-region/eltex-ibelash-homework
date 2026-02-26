#include "eltex_commander.h"

int main() {
    int ret = 0, lp_y, lp_x, rp_y, rp_x;
    WINDOW *left_panel, *right_panel;
    ret = initialize_terminal();
    if (0 > ret) {
        fprintf(stderr, "Не удалось инициализировать терминал.\n"
                        "Код ошибки: %d\nВыходим.\n", ret);
        return ret;
    }
    
    left_panel = derwin(stdscr, LINES-2, (COLS/2)-1, 1, 1);
    right_panel = derwin(stdscr, LINES-2, (COLS/2)-1, 1, (COLS+1)/2);

    do {
        werase(left_panel);
        wresize(left_panel, LINES-2, (COLS/2)-1);
        werase(right_panel);
        mvderwin(right_panel, 1, COLS/2);
        wresize(right_panel, LINES-2, ((COLS+1)/2)-1);
        box(stdscr, '|', '-');
        box(left_panel, 'l', '-');
        box(right_panel, 'r', '-');
        getmaxyx(left_panel, lp_y, lp_x);
        getmaxyx(right_panel, rp_y, rp_x);
        wprintw(left_panel, "Размеры терминала %d x %d\n", LINES, COLS);
        wprintw(left_panel, "Размеры панели %d x %d\n", lp_y, lp_x);
        wprintw(right_panel, "Размеры панели %d x %d\n", rp_y, rp_x);
        refresh();
    } while('q' != getch());
    

    delwin(left_panel);
    delwin(right_panel);
    endwin();
    return ret;
}
