#include <errno.h>
#include <stdio.h>
#include <unistd.h>

int main() {
  char BUFF[1024];
  int lu;

  while ((lu = read(3, &BUFF, 1024)) > 0) {
    int a_ecrire = lu;
    char *pos = BUFF;

    while(a_ecrire) {
      int ecrit = write(1, pos, a_ecrire);
      a_ecrire -= ecrit;
      pos += ecrit;
    }
  }
  if (lu < 0)
    perror("problème de lecture");

  return 0;
}
