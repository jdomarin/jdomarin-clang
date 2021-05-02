#include <stdio.h>
#include <errno.h>
#define BUFFSIZE 1024

int main(int argc, char** argv) {

  int nb_lus, nb_ecrits;
  char* buf;
  int a_ecrire;
  char* pos_buff;
  FILE* fich1, fich2;

  while (nb_lus = read(fich1, buf, BUFFSIZE)){
    if ((nb_lus == -1) && (errno!=EINTR)){
      break; /*erreur*/
    } else if(nb_lus > 0) {
      pos_buff = buf;
      a_ecrire = nb_lus;
      while(nb_ecrits = write(fich2, pos_buff, a_ecrire)) {
	if((nb_ecrits == -1) && (errno!=EINTR))
	  break; /*erreur*/
	else if (a_ecrire == 0)
	  break; /*fini*/
	else if (nb_ecrits > 0) {
	  pos_buff += nb_ecrits;
	  a_ecrire -= nb_ecrits;
	}
      }
    }
  }
  return 0;
}
