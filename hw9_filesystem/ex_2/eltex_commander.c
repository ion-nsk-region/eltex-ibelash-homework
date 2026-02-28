#include "eltex_commander.h"

int main() {
    int ret = 0, 
        t_y, t_x, //< Размеры основного окна (терминала)
        lp_y, lp_x, //< Размеры левой панели
        rp_y, rp_x; //< Размеры правой панели
    WINDOW *left_panel, *right_panel;

    ret = initialize_terminal();
    if (0 > ret) {
        fprintf(stderr, "Не удалось инициализировать терминал.\n"
                        "Код ошибки: %d\nВыходим.\n", ret);
        return ret;
    }
    
    getmaxyx(stdscr, t_y, t_x);
    left_panel = derwin(stdscr, t_y - 2, (t_x / 2), 1, 0);
    if (NULL == left_panel) {
        fprintf(stderr, "Не удалось создать левую панель.\n"
                        "Выходим.\n");
        return -1;
    }

    right_panel = derwin(stdscr, t_y - 2, (t_x / 2), 1, (t_x + 1) / 2);
    if (NULL == right_panel) {
        fprintf(stderr, "Не удалось создать правую панель.\n"
                        "Выходим.\n");
        return -1;
    }

    do {
        clear();

        // Обрабатываем изменение размера терминала
        getmaxyx(stdscr, t_y, t_x);
        wresize(left_panel, t_y - 2, (t_x / 2));
        mvderwin(right_panel, 1, t_x / 2);
        wresize(right_panel, t_y - 2, ((t_x + 1) / 2));
        box(left_panel, ACS_VLINE, ACS_HLINE);
        box(right_panel, ACS_VLINE, ACS_HLINE);

        // выводим размеры терминала, левой и правой панели.
        getmaxyx(left_panel, lp_y, lp_x);
        getmaxyx(right_panel, rp_y, rp_x);
        mvprintw(0, 0, "%dx%d  L %dx%d  R %dx%d", t_y, t_x, lp_y, lp_x, rp_y, rp_x);

        // Собственно вывод на экран
        refresh();
    } while('q' != getch());
    

    delwin(left_panel);
    delwin(right_panel);
    endwin();
    return ret;
}
