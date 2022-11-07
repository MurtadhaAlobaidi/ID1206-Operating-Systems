#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

int main(int argc, char const *argv[]) {
  int pid = fork();

  int fd[2];

  if (pid == 0) {
    close(fd[0]);

    execl("ls", "ls", (char *)NULL);
    perror("execlp ls");

  } else {
    close(fd[1]);

    execl("wc", "wc", "-l", (char *)NULL);
    perror("execlp wc");
  }

  if (pipe(fd) == -1) {
    perror("Eror pipe\n");
    exit(1);
  }

  int pid = fork();

  if (pid == -1) {
    perror("fork error\n");
    exit(2);
  }

  return 0;
}
