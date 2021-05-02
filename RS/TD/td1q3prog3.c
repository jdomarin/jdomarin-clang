#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main() {
  if (fork())
    fork();
  printf("hello!\n");
  exit(0);
}
