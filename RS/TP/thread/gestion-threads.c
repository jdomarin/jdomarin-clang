#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#define NUM_THREADS 3

void *travail(void *null) {
  int i; 
  double result = 0.0;
  for (i = 0; i < 1000000 ; i++) 
    result = result + (double)random();
  printf("Resultat = %e\n", result);
  pthread_exit((void *) 0);
}

int main(int argc, char **argv) {
  pthread_t thread[NUM_THREADS];
  pthread_attr_t attr;
  int rc, t, status;
  /*Initialise et modifie l'attribut*/
  pthread_attr_init(&attr);
  pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_JOINABLE);

  for(t=0; t<NUM_THREADS; t++) {
    printf("Creating thread %d\n", t);
    if((rc = pthread_create(&thread[t], &attr, travail, NULL))) {
      printf("ERREUR de _create() : %d\n", rc);
      exit(-1);
    }
  }

  /* Libère l'attribut */
  pthread_attr_destroy(&attr);
  /* Attend les autres */
  for (t = 0; t < NUM_THREADS; t++) {
    if ((rc = pthread_join(thread[t], (void**)&status))) {
      printf(" ERREUR de _join() : %d\n", rc);
      exit(-1);
    }
    printf("Rejoint thread %d. (ret=%d)\n", t, status);
  }
  pthread_exit(NULL);
}
