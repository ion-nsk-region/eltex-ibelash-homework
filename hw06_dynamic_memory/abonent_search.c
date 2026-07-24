#include "abonent_dir.h"

struct Abonent *abonent_search(struct Abonent *start, char name[FIELD_SIZE]) {
  if(NULL == start) {
    return NULL;
  }
  do {  
    if (0 == string_compare(name, start->name)) {
      return start;
    }
    start = start->next;
  } while(NULL != start);

  return NULL;  // ничего не найдено
}
