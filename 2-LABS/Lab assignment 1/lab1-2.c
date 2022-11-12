#include <dirent.h> //files
#include <errno.h>  /* error handling */
#include <fcntl.h>  // mq_open
//#include <mqueue.h> /* Queue functions */
#include <stdio.h>  //input and output
#include <stdlib.h> // library
#include <string.h> //Size_t  and strlen
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>

void read() {
  FILE *file;
  file = fopen("text.txt", "r");
  char r;
  while (!feof(file)) {
    r = fgetc(file);
    printf("%c", r);
  }
  fclose(file);
}

// int write() {}

int main(int argc, char const *argv[]) {

  read();
  printf("This in the file \n");

  return 0;
}
