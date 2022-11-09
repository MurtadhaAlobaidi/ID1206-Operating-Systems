#include <dirent.h> //files
#include <errno.h>  /* error handling */
#include <fcntl.h>  // mq_open
#include <mqueue.h> //Queue
#include <stdio.h>  //input and output
#include <stdlib.h> // library
#include <string.h> //Size_t  and strlen
#include <sys/stat.h>

int processes_1(struct mqdes, const char *msg_ptr, size_t msg_len, ...) {
  FILE *file = fdopen("2-LABS/Lab assignment 1/file.txt", "r");
}

int processes_2() {}

int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}
