#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <errno.h>
#define N 2

int main() {
  int status, i;
  pid_t pid[N+1];

  for (i=0; i<N; i++)
    if ((pid[i] = fork()) == 0) /*fils*/
      exit(100+i);


  pid_t pid2;
  i = 0;
  /*le père attend la fin de ses fils*/
  while ((pid2 = waitpid(pid[i++], &status, 0)) > 0) {
    if (WIFEXITED(status))
      if (WEXITSTATUS(status) == 0) {
	printf("Le fils %d s'est terminé normalement avec le code 0.\n", pid);
	printf("Il n'a donc pas rencontré de problème");
      } else {
	printf("Le fils %d s'est terminé avec le code %d.\n", pid, WEXITSTATUS(status));
	printf("Il s'agit en général d'un code d'erreur (cf. la page man du processus déclenché).\n");
      }
    else
      printf("Le fils %d s'est terminé à cause d'un signal\n", pid);
}
if (errno != ECHILD)
  perror("erreur dans waitpid");

exit(0);
}
