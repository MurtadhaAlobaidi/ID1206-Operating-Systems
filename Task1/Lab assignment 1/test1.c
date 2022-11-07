#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <time.h>
#include <unistd.h>

// 1-Use fork to make a child process
// 2-the child process executes ls
// 3-passing the result (i.e., the list files/directories)
// through a pipe to the parent process.

// 4- The parent executes wc -l to print out
// the number of lines for the list passed by the child.
// Titta sida 900 i boken the Linux

int main(int argc, char const *argv[]) {
  int fd[2]; // fd[0] read , fd[1]write
  if (pipe(fd) == -1) {
    perror("Eror pipe\n");
    exit(1);
  }

  int pid = fork();

  if (pid == -1) {
    perror("fork error\n");
    exit(2);
  }

  if (pid > 0) {
    close(fd[0]);
    // /* Defensive check */
    // if (fd[1] != STDOUT_FILENO) {
    //   if (dup2(fd[1], STDOUT_FILENO) == -1) {
    //     perror("dup2");
    //     if (close(fd[1]) == -1) {
    //       perror("close 2");
    //     }
    //   }
    /* Writes to pipe */
    execl("ls", "ls", (char *)NULL);
    perror("execlp ls");
    // }
  } else {
    close(fd[1]);
    /* Reads from pipe */
    execl("wc", "wc", "-l", (char *)NULL);
    perror("execlp wc");
  }

  // switch (fork()) {
  // case -1: // fork erorr
  //   perror("fork");
  // case 0:                   // Child exec 'ls' to write to pipe
  //   if (close(fd[0]) == -1) // read and is unused
  //   {
  //     perror("close 1");
  //   }
  //   /* Defensive check */
  //   if (fd[1] != STDOUT_FILENO) {
  //     if (dup2(fd[1], STDOUT_FILENO) == -1) {
  //       perror("dup2");
  //       if (close(fd[1]) == -1) {
  //         perror("close 2");
  //       }
  //     }
  //     /* Writes to pipe */
  //     execl("ls", "ls", (char *)NULL);
  //     perror("execlp ls");

  //     /* Parent */
  //   default:
  //     /* Reads from pipe */
  //     execl("wc", "wc", "-l", (char *)NULL);
  //     perror("execlp wc");
  //     break;
  //   }
  // }

  // // fork() creates a new process.
  // // fork() is called once, but it returns twice.
  // int pid = fork();
  // // the pid of the new child → to the parent.
  // if (pid == -1) {
  //   perror("fork");
  //   exit(1);
  // }
  // // 0 → to the child.
  // if (pid > 0) {
  //   close(fd[0]);
  //   // the child
  //   const char x = execlp("ls", "-a", NULL);
  //   //printf("%d\n",x);
  //   if (write(fd[1], &x, (int)getpid()) == -1) {
  //     perror("Error pip write\n");
  //     exit(1);
  //   }
  //   close(fd[1]);

  // } else {
  //   close(fd[1]);
  //   int r;
  //   if (read(fd[0], &r, (int)getpid()) == -1) {
  //     perror("Error pip read\n");
  //     exit(1);
  //   }
  //  // close(fd[0]);
  //   // parent
  //   wait(NULL);
  //  // printf("Passing from child! %d\n",r);
  //   // printf("Processing\n");
  // }

  return 0;
}
