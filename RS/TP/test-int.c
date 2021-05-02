#include <signal.h>
#include <stdio.h>
#include "../test-int.h"
#include <stdlib.h>
#include <string.h>

void handler(int sig) {
  printf("signal SIGINT reçu!\n");
  exit(0);
}

int main(){
  struct sigaction nvt,old;
  memset(&nvt, 0, sizeof(nvt));
  nvt.sa_handler = &handler;
  sigaction(SIGINT, &nvt, &old);
  pause();
  printf("Ceci n'est jamais affiché.\n");
}
