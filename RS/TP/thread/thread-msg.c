#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 8

typedef struct data {
  int thread_id, sum;
  char *msg;
} data_t;

data_t data_array[NUM_THREADS];

void *PrintHello(void *arg) {
  data_t *mine = (data_t *)arg;

  sleep(1);
  printf("Thread %d : %s Sum=%d\n", mine->thread_id, mine->msg, mine->sum);
  pthread_exit(NULL);
}

int main(int argc, char **argv) {
  pthread_t threads[NUM_THREADS];
  int rc, t, sum = 0;

  char *messages[NUM_THREADS] = {
    "EN : Hello World!", "FR : Bonjour, le monde !", "SP : Hola, al mundo!", "RU : Zdravstvytye, mir!", "DE : Guten Tag, Welt!", "Klingon : Nuq NeH!", "JP : Sekai e konnichiwa!", "Latin : Orbis, te saluto!" };

  for(t = 0; t < NUM_THREADS ; t++) {
    sum = sum + t;
    thread_data_array[t].thread_id = t;
    thread_data_array[t].sum = sum;
    thread_data_array[t].message = messages[t];
    printf("Creating thread %d\n", t);
    rc = pthread_create(&threads[t], NULL, PrintHello, (void*)thread_data_array[t]);
    if (rc) {
      printf("ERROR ; _create() returned %d\n", rc);
      exit(-1);
    }
  }
  pthread_exit(NULL);
}
