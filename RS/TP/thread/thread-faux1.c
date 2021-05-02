#include <pthread.h>
#include <stdio.h>

void *hello(void *id) {
  printf("%d : hello world \n", (char*) id);
  pthread_exit(NULL);
}

int main(int argc, char * argv[]) {
  pthread_t th[3];
  int i;

  for(i=0; i<3; i++) {
    printf("Crée thread %d\n", i);
    pthread_create(&th[i], NULL, hello, (void *)&i);
  }

  pthread_exit(NULL);
}
