#include <stdio.h>
#include <unistd.h>

int main() {
  if (fork()==0) {
    if (fork()) {
      printf("hello!\n");
    }
  }
}
