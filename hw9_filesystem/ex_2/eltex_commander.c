#include "eltex_commander.h"

int main() {
    int ret = 0, line = 0, col = 0;
    ret = initialize_terminal();
    if (0 > ret) {
        printf("Не удалось инициализировать терминал.\n"
                        "Код ошибки: %d\nВыходим.\n", ret);
    }
    
    printw("Привет! 🤓\n\n");

    do {
        getyx(stdscr, line, col);
        line = line - 1;
        col = 0;
        move(line, col);
        clrtoeol();
        printw("Мои размеры %d x %d\n", LINES, COLS);
        refresh();
    } while('q' != getch());
    

    endwin();
    return ret;
}
