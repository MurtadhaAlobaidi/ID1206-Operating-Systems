#include <dirent.h> //files
#include <errno.h>  /* error handling */
#include <fcntl.h>  // mq_open
//#include <mqueue.h> /* Queue functions */
#include <stdio.h>  //input and output
#include <stdlib.h> // library
#include <string.h> //Size_t  and strlen
#include <sys/stat.h>

int read() {
  FILE *file;
  file = fopen("file.txt", "r");
  char r;
  while (!feof(file)) {
    r = fgetc(file);
    printf("%c", r);
  }
  fclose(file);

  return r;
}

// int write() {}

int main(int argc, char const *argv[]) {
  read();
  return 0;
}
