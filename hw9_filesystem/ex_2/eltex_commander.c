#include "eltex_commander.h"

int main() {
    int ret = 0;
    ret = initialize_terminal();
    if (0 > ret) {
        printf("Не удалось инициализировать терминал.\n"
                        "Код ошибки: %d\nВыходим.\n", ret);
    }
    
    printw("Привет! 🤓");

    refresh();
    getch();

    endwin();
    return ret;
}
