#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>

int main(int argc, const char * argv[]) {
    //printf("Hello, World!\n");
    
    //fork() creates a new process.
    //fork() is called once, but it returns twice.
    pid_t fork(void);
    //The PID of the new child → to the parent.
    pid_t pid = fork();
    if (pid == -1) {
      perror("fork");
      exit(1);
    }
    //0 → to the child.
    if (pid > 0)
      printf("I am the parent of pid = %d!\n", pid);
    else
      printf("I am the child!\n");
    
    return 0;
}