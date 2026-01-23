#include "abonent_dir.h"

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
