#include <stdio.h>

int round_float(float f) {
  // Works for +ve f values.
  // return (f-(int)f>=0.5)? ((int)f)+1: (int)f;
  
  // Works for +ve & -ve f values.
  return (int)(f < 0 ? f - 0.5 : f + 0.5);
}

void main() {
  float f;

  f = 12.4;
  printf("f:%f, round:%d\n", f, round_float(f));
  f = 12.5;
  printf("f:%f, round:%d\n", f, round_float(f));
  f = 12.6;
  printf("f:%f, round:%d\n", f, round_float(f));
}
