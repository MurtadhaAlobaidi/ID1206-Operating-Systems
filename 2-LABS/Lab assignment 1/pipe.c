#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>
// https://tldp.org/LDP/lpg/node11.html
int main(void) {
  int fd[2], nbytes;
  pid_t childpid;
  char string[] = "Hello, world 2022!\n";
  char readbuffer[80];

  extern unsigned long strlen(const char *);
  pipe(fd);

  if ((childpid = fork()) == -1) {
    perror("fork");
    exit(1);
  }

  if (childpid == 0) {
    /* Child process closes up input side of pipe */
    close(fd[0]);

    /* Send "string" through the output side of pipe */
    write(fd[1], string, (strlen(string) + 1));
    exit(0);
  } else {
    /* Parent process closes up output side of pipe */
    close(fd[1]);
    wait(NULL);
    /* Read in a string from the pipe */
    nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
    printf("Received string: %s", readbuffer);
  }

  return (0);
}