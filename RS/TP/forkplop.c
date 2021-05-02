#include <unistd.h>
#include <stdio.h>

pid_t plop() {
  fork();
  printf("plop\n");
  return fork();
}

int main() {
  if(plop())
    if(plop())
      printf("yes\n");
}
/*affichage : 6 plop et 4 yes*/

