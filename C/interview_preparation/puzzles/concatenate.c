#include <stdio.h>

#define CONCAT(a, b) a##b

int get_second() { return 456; }

int main(void) {

  // Works
  printf("%d\n", CONCAT(123, 456));

  // Does not work
  // printf("%d\n", CONCAT(123, get_second()));

  return 0;
}
