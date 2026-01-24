#include "abonent_dir.h"

int abonent_del(struct Directory *dir, struct Abonent *the_abonent) {
  // проверяем, что справочник существует, не пустой, не поломанный 
  // (ссылки на голову и хвост не пустые)
  if(NULL == dir || NULL == dir->head || NULL == dir->tail || 0 == dir->size) {
    return -1;
  }
  
  if(NULL != the_abonent->prev) {
    /*   v----<-------<-----<-prev
     * prev <-- the_abonent --> next
     *   next ->---->---->-------^
     */
    the_abonent->prev->next = the_abonent->next;
  } else {
    dir->head = the_abonent->next;
  }

  if(NULL != the_abonent->next) {
    the_abonent->next->prev = the_abonent->prev;
  } else {
    dir->tail = the_abonent->prev;
  }

  dir->size--;

  free(the_abonent);
  the_abonent = NULL;

  return 0;
}
