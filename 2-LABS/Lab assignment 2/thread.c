#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/_pthread/_pthread_mutex_t.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
/*
 * From Lecture_5
 * */

int buffer = 0;
pthread_mutex_t lock;

void *thread_func(void *arg) {
  pthread_mutex_lock(&lock);
  char *buf = (char *)malloc(sizeof(int));
  *buf = 0;
  while (buffer < 15) {

    (*buf)++, buffer++, pthread_mutex_unlock(&lock);
    printf("TID: %d\t PID: %d\t Buffer: %d\n", (int)pthread_self(), getpid(),
           buffer);
  }

  pthread_mutex_unlock(&lock);
  return buf;
}

int main(void) {

  pthread_t threads123[3];
  pthread_mutex_init(&lock, NULL);

  int i = 0;
  while (i < 3) {
    pthread_create(&threads123[i++], NULL, thread_func, NULL);
  }
  /* inspiration from
   * https://stackoverflow.com/questions/62752275/pthread-join-and-void-error-understanding
   * */
  for (int i = 0, *mod; i < 3; printf("TID %d worked on the buffer %d times\n ",
                                      (int)threads123[i++], *mod)) {
    pthread_join(threads123[i], (void **)&mod);
  }

  printf("Total buffer accesses: %d \n", buffer);

  return 0;
}