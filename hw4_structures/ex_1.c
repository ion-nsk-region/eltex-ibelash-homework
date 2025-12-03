#include <stdio.h>

#define DIR_SIZE 100
#define FIELD_SIZE 10

struct abonent {
  char name[FIELD_SIZE];
  char second_name[FIELD_SIZE];
  char tel[FIELD_SIZE];
};

int menu();

// ====================================================================
int main() {
  struct abonent directory[DIR_SIZE];
  int directory_size = 0;
  int menu_item = 0;

  while (5 != menu_item) {
    menu_item = menu();
    if (-1 == menu_item) {
      printf(
          "Ошибка: такого пункта меню не существует.\n"
          "        Пожалуйста введите только одну цифру.\n");
    }
    switch (menu_item) {
      case 1:
        if(0 == abonent_add(directory)) {
            directory_size++;
        }
        break;
      case 2:
        abonent_del();
        break;
      case 3:
        abonent_search();
        break;
      case 4:
        list_all_abonents();
        break;
      case 5:
        printf("Выходим.\n");
        break;
      default:
        printf("Ошибка: пункт меню %d) всё ещё в разработке.\n", menu_item);
        printf("Пожалуйста, выберите другой пункт меню.\n");
        break;
    }
  }

  return 0;
}
// ====================================================================

int menu() {
  int item;
  printf("1) Добавить абонента\n");
  printf("2) Удалить абонента\n");
  printf("3) Поиск абонентов по имени\n");
  printf("4) Вывод всех записей\n");
  printf("5) Выход\n");

  if (1 != scanf("%d", &item)) {
    return -1;
  }
  if (item < 1 || item > 5) {
    return -1;
  }
  return item;
}

int abonent_add(struct abonent directory[DIR_SIZE]) { 
        struct abonent new_abonent;
        if(0 != field_input(new_abonent.name)) {
            printf("Новая запись не создана. Попробуйте снова.\n");
            return 1;
        }
        if(0 != field_input(new_abonent.second_name)) {
            printf("Новая запись не создана. Попробуйте снова.\n");
            return 2;
        }
        if(0 != field_input(new_abonent.tel)) {
            printf("Новая запись не создана. Попробуйте снова.\n");
            return 3;
        }
        // TODO найти пустую запись и записать нового абонента в пустую запись

        return 0;
}

int field_input(char field[FIELD_SIZE]) {
        char buf[BUFSIZ];
        if (NULL == fgets(buf, sizeof(buf), stdin)) {
            printf("Ошибка при чтении данных.");
            return 1;
        }
        if ('\n' == buf[0]) {
            printf("Ошибка: Кажется ничего не введено.\n"
                   "Пожалуйста, введите хоть что-нибудь.\n");
            return 2;
        }
        
        int i = 0, n = FIELD_SIZE - 1;
        while('\0' != buf[i] && i < BUFSIZ) {
            i++;
        }
        if (i > n) {
            printf("Ошибка: Введённые данные больше %d байт.\n"
                   "Введите до %d символов латиницы или до %d "
                   "символов кириллицы.\n", n, n, n/2);
            return 3;
        }

        while(i >= 0) {
            field[i] = buf[i];
           i--; 
        }
    return 0;
}
