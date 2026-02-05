#include "calc.h"

int calc_input(int *a, int *b) {
    char buf[BUFSIZ];
    int ret;

    printf("Введите два аргумента через пробел: ");
    
    if(NULL == fgets(buf, sizeof(buf), stdin)) {
        printf("Ошибка при чтении данных.\n");
        return 1;
    }

    if('\n' == buf[0]) {
        printf("Ошибка: пустой ввод.\n");
        return 2;
    }

// замена переноса строки на конец строки
    int i = 0;
    while('\n' != buf[i] && i < BUFSIZ) {
        i++;
    }
    buf[i] = '\0'; 

    ret = sscanf(buf, "%d%d", a, b);
    if(EOF == ret || ret < 2) {
        printf("Ошибка: не все аргументы были распознаны.\n");
        return 3;
    }

    return 0;
}
