#include <pthread.h>
#include <stdio.h>

void *hello(void *arg) {
  int *id = (int*)arg;
  printf("%d : hello world\n", *id);
  pthread_exit(NULL);
}

int main(int argc, char **argv) {
  pthread_t thread[3];
  int id[3] = {1, 2, 3};
  int i;

  for(i = 0; i < 3 ; i++){
    printf("Crée thread %d\n", i);
    pthread_create(&thread[i], NULL, hello, (void *)&id[i]);
  }
  pthread_exit(NULL);
}
