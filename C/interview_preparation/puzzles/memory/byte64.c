#include <malloc.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

/*
 *
 * Problem statement:
 *
 * Write a malloc256 that returns a pointer to a 256 byte-aligned memory
 * on the heap.
 *
 * Write a corresponding free256.
 *
 */

// Technique 1: Using memalign

char *malloc256(int n) {
  char *ptr = (char *)memalign(256, n);
  printf("malloc256 modified to p:%p\n", ptr);
  return ptr;
}

void free256(char *ptr) {
  printf("free64 modified to ptr:%p\n", ptr);
  free(ptr);
}

// Technique 2: Custom memalign

#define ALIGNMENT 256
#define OFFSET_STORE 4 

char *my_malloc256(int n) {

  char *orig_ptr = (char *)malloc(n + ALIGNMENT + OFFSET_STORE);
  char *ptr = orig_ptr + 4;
  char *ptr256 = (char *)(((uintptr_t)ptr + ALIGNMENT - 1) & (~0xFF));
  uint32_t *offset_ptr = (uint32_t *)(ptr256 - OFFSET_STORE);
  *offset_ptr = ptr256 - orig_ptr;

  printf("my_malloc256 orig ptr:%p\n", orig_ptr);
  // printf("my_malloc256 start ptr:%p\n", ptr);
  printf("my_malloc256 ptr256 ptr:%p\n", ptr256);
  // printf("my_malloc256 offset ptr:%p\n", offset_ptr);
  // printf("my_malloc256 offset %d\n", *offset_ptr);

  return ptr256;
}

void my_free256(char *ptr256) {
  uint32_t offset = *((uint32_t *)(ptr256 - OFFSET_STORE));
  char *orig_ptr = ptr256 - offset;

  printf("my_free256 ptr256 ptr:%p\n", ptr256);
  // printf("my_free64 offset:%d\n", offset);
  printf("my_free256 orig ptr:%p\n", orig_ptr);

  free(orig_ptr);
}

int main() {
  int n = 40;
  char *p;

  p = my_malloc256(n);
  printf("\ngot p:%p\n\n", p);
  my_free256(p);

  return 0;
}
