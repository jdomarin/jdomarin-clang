#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "test-int.h"

void handler(int sig){
  printf("trop tard\n");
  exit(1);
}

int main() {
  struct sigaction nvt,old;
  int reponse, restant;
  memset(&nvt, 0, sizeof(nvt));
  nvt.sa_handler = handler;
  sigaction(SIGALRM, &nvt, &old);
  printf("Entrez un nombre avant 5 sec : ");
  alarm(5);
  scanf("%d", &reponse);
  restant = alarm(0);
  printf("bien reçu (en %d secondes) \n", 5-restant);
  exit(0);
}
