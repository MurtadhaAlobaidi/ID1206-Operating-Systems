#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

pid_t wait(int *status);

int main (void) {
  int status;
  pid_t pid;
if (fork() == 0) return 1;
    // the child pid = wait(&status);
if (pid == -1)
    perror("wait");
    printf("pid = %d\n", pid);
return 0;
    
}