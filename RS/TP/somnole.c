#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

void somnole(int n) {
  int i;
  for (i = 1 ; i <= n; i++) {
    sleep(1);
    printf("Déjà dormi %d secondes sur %d\n", i, n);
  }
}

int main(int argc, char **argv) {
  somnole(atoi(argv[1]));

  return 0; 
}
