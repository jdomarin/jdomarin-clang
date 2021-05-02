#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>


int main() {
  int status;
  pid_t pid;

  fprintf(stderr, "Hello!\n");
  pid = fork();
  fprintf(stderr, "%d\n", !pid);
  if (pid != 0) {
    if (waitpid(-1, &status, 0) > 0) {
      if(WIFEXITED(status) != 0)
	fprintf(stderr, "%d\n", WEXITSTATUS(status));
    }
}
fprintf(stderr, "Bye\n");
exit(2);
}
