#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(void) {
  int fd;
  fd = open("toto", O_RDWR); /*doit exister*/
  while(1) {
    if(lockf(fd, F_LOCK, 0) == 0) {
      printf("%d : verrouille le fichier\n", getpid());
      sleep(5);
      if(lockf(fd, F_ULOCK, 0) == 0)
	printf("%d : déverrouille le fichier\n", getpid());
      return;
    } else {
      printf("%d : déjà verrouillé...\n", getpid());
      sleep(2);
    }
  }
}
