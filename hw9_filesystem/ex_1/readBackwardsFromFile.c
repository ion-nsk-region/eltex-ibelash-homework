#include <string.h>

#include "ex_1.h"

void readBackwardsFromFile(const char *filename, char *string_in) {
  ssize_t bytes_read = 0;
  off_t current_offset;
  int fd;
  char c, buf[BUFSIZ] = "Мы это не увидим, если всё работает.";

  openFile(filename, O_RDONLY, &fd); // открываем на чтение
  if (-1 == fd) {
    fprintf(stderr, "Не могу открыть файл %s\n", filename);
    return;
  }

  // Встаём в конец файла
  errno = 0;
  current_offset = lseek(fd, -1, SEEK_END);
  if (-1 == current_offset && 0 != errno) {
    perror("lseek");
    closeFile(fd);
    return;
  }

  // Читаем задом наперёд в буфер
  int i = 0;
  while (0 <= current_offset && i < BUFSIZ) {
    errno = 0;
    bytes_read = read(fd, &c, 1);
    if (-1 == bytes_read && 0 != errno) {
      perror("read");
      break;
    }
    buf[i] = c;
    i++;
    // чтобы читать в обратном направлении смещаемся назад
    // на два байта, так как только что сместились вперёд
    // на один при чтении. -1 = -2 + 1
    current_offset = lseek(fd, -2, SEEK_CUR);
  }
  buf[i] = '\0';
  sprintf(string_in, "%s", buf);

  closeFile(fd);
}
