/// \file
/// \brief Единственный файл.
/// \details Здесь реализована вся функциональность справочника.
/// \authors Иван Белаш
/// \date 2025-12-03
/// \warning Данный справочник создан только в учебных целях

#include <stdio.h>

#define DIR_SIZE 100 ///< Размер справочника
#define FIELD_SIZE 10 ///< Размер поля для ввода данных

/*!
 * \brief Структура, хранящая имена и телефоны абонентов.
 *
 * По каждому абоненту в справочнике хранится следующая информация:
 * - имя 
 * - второе имя (фамилия)
 * - телефон.
 *
 * Размер данных не более #FIELD_SIZE символов для латиницы и в два раза меньше
 * для кириллицы.
 */
struct abonent {
  char name[FIELD_SIZE]; ///< Имя абонента 
  char second_name[FIELD_SIZE]; ///< Второе имя (Фамилия) абонента
  char tel[FIELD_SIZE]; ///< Номер телефона абонента
};

/*!
 * \brief Создаёт новую запись об абоненте. 
 *
 * Новая запись помещается в первую свободную (заполненную нулями) ячейку.
 * \param[in,out] directory Ссылка на справочник (массив) с абонентами.
 * \return Код ошибки, где:
 * - 0 - всё в порядке
 * - 1 - произошла ошибка во время ввода имени
 * - 2 - произошла ошибка во время ввода второго имени
 * - 3 - произошла ошибка во время ввода телефона    
 * \todo Передавать в сообщение об ошибке код ошибки из функции #field_input.
 */
int abonent_add(struct abonent directory[DIR_SIZE]);
int abonent_del_interactive(struct abonent directory[DIR_SIZE]);
void abonent_del(struct abonent *abonent);
void abonent_print(struct abonent abonent);
int abonent_search(struct abonent directory[DIR_SIZE], char name[FIELD_SIZE],
                   int start);
void clear_dir(struct abonent directory[DIR_SIZE]);
int directory_search(struct abonent directory[DIR_SIZE], int dir_size);
int field_input(char field[FIELD_SIZE]);
void list_all_abonents(struct abonent directory[DIR_SIZE]);
int menu();
int string_compare(char string1[], char string2[]);

// ====================================================================
int main() {
  struct abonent directory[DIR_SIZE];
  int directory_size = 0;
  int menu_item = 0;

  clear_dir(directory);

  while (5 != menu_item) {
    menu_item = menu();

    switch (menu_item) {
      case -1:
        printf(
            "Ошибка: Такого пункта меню не существует.\n"
            "        Пожалуйста введите только одну цифру.\n");
        break;
      case 1:
        if (100 <= directory_size) {
          printf(
              "Ошибка: Превышен допустимый размер справочника.\n"
              "        Пожалуйста, удалите лишние записи.\n");
          break;
        }
        if (0 == abonent_add(directory)) {
          directory_size++;
        }
        break;
      case 2:
        if (0 == abonent_del_interactive(directory)) {
          directory_size--;
        }
        break;
      case 3:
        if (0 >= directory_size) {
            printf("Справочник пуст.\n");
            break;
        }
        if (0 != directory_search(directory, directory_size)) {
          printf("Ошибка: Неверный ввод. Пожалуйста, введите снова.");
        }
        break;
      case 4:
        if(0 < directory_size) {
                list_all_abonents(directory);
            printf("Всего абонентов: %d\n", directory_size);
        } else {
            printf("Справочник пуст.\n");
        }
        break;
      case 5:
        printf("Выходим.\n");
        break;
      default:
        printf("Ошибка: Пункт меню %d) всё ещё в разработке.\n", menu_item);
        printf("        Пожалуйста, выберите другой пункт меню.\n");
        break;
    }
  }

  return 0;
}
// ====================================================================

int menu() {
  int item;
  printf("\n1) Добавить абонента\n");
  printf("2) Удалить абонента\n");
  printf("3) Поиск абонентов по имени\n");
  printf("4) Вывод всех записей\n");
  printf("5) Выход\n");

  if (1 != scanf("%d", &item)) {
    return -1;
  }
  scanf("%*c");  // считываем и выбрасываем перенос строки из буфера

  if (item < 1 || item > 5) {
    return -1;
  }
  return item;
}

int abonent_add(struct abonent directory[DIR_SIZE]) {
  struct abonent new_abonent;
  int index;

  printf("Введите имя: ");
  if (0 != field_input(new_abonent.name)) {
    printf("Новая запись не создана. Попробуйте снова.\n");
    return 1;
  }

  printf("Введите фамилию: ");
  if (0 != field_input(new_abonent.second_name)) {
    printf("Новая запись не создана. Попробуйте снова.\n");
    return 2;
  }

  printf("Введите телефон: ");
  if (0 != field_input(new_abonent.tel)) {
    printf("Новая запись не создана. Попробуйте снова.\n");
    return 3;
  }

  index = abonent_search(directory, "000000000\0", 0); 
  // Мы предполагаем что никто не станет вводить имя из одних только нулей

  for (int i = 0; i < FIELD_SIZE - 1; i++) {
    directory[index].name[i] = new_abonent.name[i];
    directory[index].second_name[i] = new_abonent.second_name[i];
    directory[index].tel[i] = new_abonent.tel[i];
  }

  return 0;
}

int field_input(char field[FIELD_SIZE]) {
  char buf[BUFSIZ];
  int i = 0, n = FIELD_SIZE - 1;

  if (NULL == fgets(buf, sizeof(buf), stdin)) {
    printf("Ошибка при чтении данных.");
    return 1;
  }
  if ('\n' == buf[0]) {
    printf(
        "Ошибка: Кажется ничего не введено.\n"
        "Пожалуйста, введите хоть что-нибудь.\n");
    return 2;
  }

  while ('\n' != buf[i] && i < BUFSIZ) {
    i++;
  }
  buf[i] = '\0';  // заменяем перенос строки на конец строки
                  // Возможно надо поколдовать с вводом на Windows и Mac,
                  // но я не проверял за неимением оных под рукой.
  if (i > n) {
    printf(
        "Ошибка: Введённые данные больше %d байт.\n"
        "Введите до %d символов латиницы или до %d "
        "символов кириллицы.\n",
        n, n, n / 2);
    return 3;
  }

  while (i >= 0) {
    field[i] = buf[i];
    i--;
  }
  return 0;
}

int abonent_del_interactive(struct abonent directory[DIR_SIZE]) {
  int id;
  printf("Пожалуйста, укажите id абонента для удаления: ");
  if (1 != scanf("%d", &id)) {
    printf("Ошибка: введено не число.");
    return 1;
  }
  if (-1 >= id || DIR_SIZE <= id) {
    printf("Ошибка: id за пределами возможных значений от 0 до %d\n", DIR_SIZE);
    return 2;
  }
  // Мы предполагаем, что FIELD_SIZE равно 10, отсюда такие "нулевые" строки
  if (0 == string_compare(directory[id].name, "000000000\0") &&
      0 == string_compare(directory[id].second_name, "000000000\0") &&
      0 == string_compare(directory[id].tel, "000000000\0")) {
    printf("Пустая запись. Уже удалено?\n");
    return 3;
  }

  abonent_del(&directory[id]);
  return 0;
}

void abonent_del(struct abonent *the_abonent) {
  int n = FIELD_SIZE - 1;
  for (int i = 0; i < n; i++) {
    the_abonent->name[i] = '0';
    the_abonent->second_name[i] = '0';
    the_abonent->tel[i] = '0';
  }
  the_abonent->name[n] = '\0';
  the_abonent->second_name[n] = '\0';
  the_abonent->tel[n] = '\0';
}

void clear_dir(struct abonent directory[DIR_SIZE]) {
  for (int i = 0; i < DIR_SIZE; i++) {
    abonent_del(&directory[i]);
  }
}

int directory_search(struct abonent directory[DIR_SIZE], int dir_size) {
  int index = 0, res;
  char name[FIELD_SIZE];
  printf("Введите имя для поиска: ");
  res = field_input(name);
  if (0 != res) {
    return res;
  }

  printf("id: Имя:       Фамилия:   Телефон:\n");

  for (int i = 0; i < dir_size; i++) {
    index = abonent_search(directory, name, index);
    if (-1 == index) {
      break;
    }
    printf("%3d ", index);
    abonent_print(directory[index]);
    index++;
  }
  printf("\n");
  return 0;
}

int abonent_search(struct abonent directory[DIR_SIZE], char name[FIELD_SIZE],
                   int start) {
  for (int i = start; i < DIR_SIZE; i++) {
    if (0 == string_compare(name, directory[i].name)) {
      return i;
    }
  }
  return -1;  // ничего не найдено
}

int string_compare(char string1[], char string2[]) {
  int c = 0;

  while (string1[c] == string2[c]) {
    if ('\0' == string1[c] || '\0' == string2[c]) {
      break;
    }
    c++;
  }
  if ('\0' == string1[c] && '\0' == string2[c]) {
    return 0;
  }

  return 1;
}

void abonent_print(struct abonent abonent) {
  // Позиции колонок захардкодил.
  // Иначе мультибайтные символы отображаются со смещением.
  printf("\033[5G%s\033[16G%s\033[27G%s\n", abonent.name, abonent.second_name,
         abonent.tel);
}

void list_all_abonents(struct abonent directory[DIR_SIZE]) {
  printf("id: Имя:       Фамилия:   Телефон:\n");
  for (int i = 0; i < DIR_SIZE; i++) {
    if (1 == string_compare(directory[i].name, "000000000\0")) {
      printf("%3d ", i);
      abonent_print(directory[i]);
    }
  }
}
