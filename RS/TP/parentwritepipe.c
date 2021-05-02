#define BUFSIZE 10
#include <stdio.h>
#include <sys/types.h>
#include <string.h>

int main(void) {

  char bufin[BUFSIZE] = "empty";
  char bufout[ ] = "hello";
  pid_t childpid;
  int fd[2];
  pipe(fd);
  if (fork() > 0) { /*père*/
    close(fd[0]);
    write(fd[1], bufout, strlen(bufout)+1);
  } else { /*fils*/
      close(fd[1]);
      read(fd[0], bufin, BUFSIZE);
    }
    printf("[%d] : bufin = %.*s, bufout = %s\n", getpid(), BUFSIZE, bufin, bufout);
    return 0;
  }
