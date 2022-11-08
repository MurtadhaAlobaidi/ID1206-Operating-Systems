#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {

  int pid = fork();

  if (pid == -1) {
    perror("fork error\n");
    exit(2);
  }

  // fd[0] read , fd[1]write
  int fd[2];

  if (pipe(fd) == -1) {
    perror("Eror pipe\n");
    exit(1);
  }
  // Chiled
  if (pid == 0) {
    close(fd[0]);
    /* Writes to pipe */
    execlp("ls", "ls", (char *)NULL);
    // perror("execlp ls");
  } // Parent
  else {
    close(fd[1]);
    wait(NULL);
    /* Reads from pipe */
    execlp("wc -l", " wc -l", "-l", (char *)NULL);
  }

  return 0;
}
