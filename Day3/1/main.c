#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUM_THREADS  5

int     count = 1;
pthread_mutex_t mut = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mut1 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t count_p ;
void *inc(void *t)
{
  long my_id = (long)t;
  printf("Starting inc(): thread %ld\n", my_id);
  pthread_mutex_lock(&mut);
  printf("i am trhead - %ld\n",my_id );
  count = count+1;
  printf("count %d\n", count);
  usleep(count);
  printf("i do useful work  %ld\n", my_id);
  if(count<=NUM_THREADS){
    pthread_mutex_unlock(&mut);
    printf("i wait all threads  %ld\n", my_id);
    pthread_mutex_lock(&mut1);
    pthread_cond_wait(&count_p, &mut1);
    pthread_mutex_unlock(&mut1);
    printf("i take single and began to work  %ld\n",my_id);
    }
  else{
    printf("I am last thread and i give single to other threads %ld\n",my_id);
    pthread_cond_broadcast(&count_p);
    pthread_mutex_unlock(&mut);
  }
  printf("Exit %ld\n",my_id);
  sleep(1);
  pthread_exit(NULL);
}

int main (int argc, char *argv[])
{
  int i,rc;
  long num=1;
  pthread_t threads[NUM_THREADS];
  for (i = 0; i < NUM_THREADS; i++)
  {
    printf("\t\tCreate Thread number %d\n",(i+1) );
    rc = pthread_create(&threads[i],NULL,inc,(void*)num);
    if (rc) {
      printf("ERROR; return code from pthread_create() is %d\n", rc);
      exit(-1);
    }
    num = num + 1;
  }
  printf("dasdasd\n");
  for (i = 0; i<NUM_THREADS; i++) {
    pthread_join(threads[i], NULL);
    printf("Thread #%d finished\n", (i+1));
  }
  printf ("Main(): Waited on %d  threads. Done.\n", NUM_THREADS);
  pthread_mutex_destroy(&mut);
  pthread_mutex_destroy(&mut1);
  pthread_cond_destroy(&count_p);
  pthread_exit(NULL);

}