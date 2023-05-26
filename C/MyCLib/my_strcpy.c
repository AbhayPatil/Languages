#include <stdio.h>
void MyStrCpy(char *s, char *d) {
  for (int i = 0;; i++) {
    d[i] = s[i];
    if (s[i] == '\0')
      break;
  }
  return;
}

int main() {
  char s[20] = "Old String";
  char d[20];

  MyStrCpy(s, d);
  MyStrCpy("New One", s);

  printf("d: %s\n", d);
  printf("s: %s\n", s);
  return 0;
}
