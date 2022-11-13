#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
/**
 * Hint1: Use fork to make a child process.
 * Then, the child process executes ls/,
 * passing the result (i.e., the list files/directories)
 * through a pipe to the parent process.
 * The parent executes wc -l to print out the number of lines
 * for the list passed by the child.
 */
/**
 * Hint2: You can use dup2 to redirect the output of
 * the exec to the input descriptor made by pipe.
 */

int main(int argc, char const *argv[]) {

  // fd[0] read , fd[1]write
  int fd[2];
  pipe(fd);

  int pid = fork();

  if (pid == -1) {
    perror("fork error\n");
    exit(1);
  }
  // Chiled
  if (pid == 0) {
    close(fd[0]);
    // redirect the output of the exec to the input descriptor made by pipe
    dup2(fd[1], STDOUT_FILENO);
    close(fd[1]);
    /* Writes to pipe */
    execlp("ls", "ls", "/", (char *)NULL);
  } // Parent
  else {
    close(fd[1]);
    dup2(fd[0], STDIN_FILENO);
    close(fd[0]);
    /* Reads from pipe */
    execlp("wc", " wc", "-l", (char *)NULL);
    wait(NULL);
  }
  return 0;
}