#include <stdio.h>
#include <time.h>
#include <unistd.h>

int main() {
  struct timespec start, end;

  /* Store start time here */
  // clock_gettime is a syscall
  clock_gettime(CLOCK_REALTIME, &start);

  /* Do 5 seconds of work */
  sleep(5);

  /* Store end time here */
  clock_gettime(CLOCK_REALTIME, &end);

  /* Get the time taken by program to execute in seconds */
  double duration = ((double)(end.tv_sec * 1E9 - start.tv_sec * 1E9 +
                              end.tv_nsec - start.tv_nsec)) /
                    1E9;

  printf("Time taken to execute in seconds : %f\n", duration);
  return 0;
}
