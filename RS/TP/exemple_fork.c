#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
  int i;
  for (i = 0; i < 3; i++){
   printf("plop!\n");
   fork();
 }
 printf("plop!\n");
 exit(0);
}
/* plop affiché 15 fois*/

