#include <dirent.h> //files
#include <errno.h>  /* error handling */
#include <fcntl.h>  // mq_open
#include <stdio.h>  //input and output
#include <stdlib.h> // library
#include <string.h> //Size_t  and strlen
#include <sys/stat.h>

int main(int argc, char const *argv[]) {
  FILE *ptr;
  char ch;

  // Opening file in reading mode
  ptr = fopen("file.txt", "r");  

  // Printing what is written in file
  // character by character using loop.
  do {
    ch = fgetc(ptr);
    printf("%c", ch);

    // Checking if character is not EOF.
    // If it is EOF stop eading.
  } while (ch != EOF);

  // Closing the file
  fclose(ptr);
  return 0;
}
