#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  pid_t pid;
  int x = 1;

  pid = fork();
  if(pid == 0) {
    printf("Dans fils : x=%d\n", ++x);
    exit(0);
  }

  printf("Dans père : x=%d\n", --x);
  exit(0);
}
