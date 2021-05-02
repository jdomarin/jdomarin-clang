#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  if(fork() || fork()) 
    fork();
  printf("plop!\n");
  exit(0);
}
/* plop affiché 5 fois*/

