#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

static int fd[2];

int mypopen(char *cmd, char *mode) {
  pipe(fd);
  if (fork() == 0) {
    close(fd[0]);
    dup2(fd[1], 1);
    close(fd[1]);

    execlp("sh", "-c", cmd, NULL);
  }
  close(fd[1]);
  return (fd[0]);
}

int mypclose() {
  if (fork() == 0) {
    int statut;
    if (!WIFEXITED(statut))
      waitpid(getpid(), &statut, 0);
    close(fd[1]);
  }
    return (fd[0]);
}

int main() {
  mypopen("ssh neptune", "w");
  mypopen("ls -lR", "r");

  return 0;
}
