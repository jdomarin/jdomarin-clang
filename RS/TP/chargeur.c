#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <dlfcn.h>
#include <stdlib.h>

int main(int argc, char **argv) {

  char path[256], *erreur = NULL;
  int (*mon_main)();
  void *module;
  /*Charge le module*/
  module = dlopen(argv[1], RTLD_NOW);
  if(!module) {
    fprintf(stderr, "%s\n", dlerror());
    exit(1);
  }
  /*Retrouve la fonction d'entrée*/
  mon_main = dlsym(module, "mon_main");
  erreur = dlerror();
  if(erreur != NULL) {
    perror(erreur);
    exit(1);
  }
  /*Appelle cette fonction*/
  (*mon_main)();
  /*Ferme tout*/
  dlclose(module);
  return 0;
}
