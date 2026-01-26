#include "abonent_dir.h"
// #include "yesno.h"

int abonent_del_interactive(struct Directory *dir) {
  int res;
  char name[FIELD_SIZE];
  struct Abonent *abonent = dir->head, *next;

  printf("Введите имя абонента для удаления: ");
  res = field_input(name);
  if (0 != res) {
    return res;
  }
  if (!string_compare("", name)) {
    printf("Ничего не введено. Ничего не удаляем.\n");
    return 0;
  }

  while (NULL != abonent) {
    abonent = abonent_search(abonent, name);
    if (NULL == abonent) {
      printf("Совпадений не найдено.\n");
      break;
    }
    abonent_print(*abonent);
    next = abonent->next;

    printf("Удалить абонента?");
    if (yesno()) {
      res = abonent_del(dir, abonent);
      if (0 != res) {
        printf(
            "Произошла ошибка во время удаления."
            "Код ошибки: %d\n",
            res);
        return -1;
      } else
        printf("Удалён успешно.\n");
    }
    printf("Продолжить поиск следующего совпадения?");
    if (yesno()) {
        abonent = next;
    } else break;
  }

  return 0;
}
