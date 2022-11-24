#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
/*
 * From Lecture_5
 * */

int buffer = 0;
pthread_mutex_t lock;

void *thread_func(void *arg) {

  int *buf = (int *)malloc(sizeof(int));
  *buf = 0;

  while (buffer < 13) {
    pthread_mutex_lock(&lock);
    printf("TID: %d\t PID: %d\t Buffer: %d\n", (int)(intptr_t)pthread_self(),
           getpid(), buffer);
    (*buf)++;
    buffer++;
    pthread_mutex_unlock(&lock);
  }

  return buf;
}

int main(void) {

  pthread_t threads123[3];
  pthread_mutex_init(&lock, NULL);

  pthread_create(&threads123[0], NULL, thread_func, NULL);
  pthread_create(&threads123[1], NULL, thread_func, NULL);
  pthread_create(&threads123[2], NULL, thread_func, NULL);

  int *mod;
  printf("TID %d worked on the buffer %d times\n", (int)(intptr_t)threads123[0], *mod);
  printf("TID %d worked on the buffer %d times\n", (int)(intptr_t)threads123[1], *mod);
  printf("TID %d worked on the buffer %d times\n", (int)(intptr_t)threads123[2], *mod);

  pthread_join(threads123[0], (void **)&mod);
  pthread_join(threads123[1], (void **)&mod);
  pthread_join(threads123[2], (void **)&mod);

  printf("Total buffer accesses: %d \n\n", buffer);

  return 0;
}