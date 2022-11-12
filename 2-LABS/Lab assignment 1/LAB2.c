#include <dirent.h> /* Handling directory files */
#include <errno.h>  /* EXIT codes and error handling */
#include <fcntl.h>  /* Defines requests/arguments used by mq_open */
#include <mqueue.h> /* Queue functions */
#include <stdio.h>  /* Basic input/output stream */
#include <stdlib.h> /* Standard library */
#include <string.h> /* Size_t, strlen */

int MAX_SIZE = 100;
int MAX_NUM_MSG = 10;
char buf[MAX_SIZE];
char *buf = calloc(sizeof *buf);
char buf_rec[MAX_SIZE];
char *buf_rec = calloc(sizeof *buf_rec);

int read() {
  FILE *file;
  file = fopen("text.txt", "r");
  size_t s = 0;
  if (!file) {
    perror("Error file not open ");
    exit(1);
  }
  char r;
  while (r = fgetc(file) != EOF) {
    buf[s++] = r;
    // printf("%c", r);
  }
  fclose(file);
  return r;
}

int mq_send(struct mq_attr attr, mqd_t mqd, const char *my_mq) {
  // Open an existing message queue
  mqd = mq_open(my_mq, O_WRONLY, &attr);

  // Write from "file" to the message queue
  mq_send(mqd, buf, strlen(buf), 1);

  // Close the message queue
  mq_close(mqd);

  return 0;
}

int mq_receive(struct mq_attr attr, mqd_t mqd, const char *my_mq) {
  // Create message queue
  mqd = mq_open(my_mq, O_RDONLY | O_CREAT, &attr);

  // Read the message from the message queue
  mq_receive(mqd, buf_rec, MAX_NUM_MSG, NULL);
  printf("Message: %s\n", buf);

  // Close the message queue
  mq_close(mqd);
  // removes the message queue identified by name.
  mq_unlink(my_mq);
}

// struct mq_attr attr(){
// attr mq_flags = 0; // Message queue description flags
// attr mq_maxmsg = MAX_NUM_MSG; // Maximum number of messages on queue
// attr mq_msgsize = MAX_SIZE; // Maximum message size (in bytes)
// attr mq_curmsgs = 0; // Number of messages currently in queue
// };

int main(int argc, char const *argv[]) {
  char *my_mq = "/mymq"; /* queue name */
  mqd_t mqd;             // message queue

  struct mq_attr attr;          /* queue attributes */
  attr.mq_flags = 0;            // Message queue description flags
  attr.mq_maxmsg = MAX_NUM_MSG; // Maximum number of messages on queue
  attr.mq_msgsize = MAX_SIZE;   // Maximum message size (in bytes)
  attr.mq_curmsgs = 0;          // Number of messages currently in queue

  read();

  mq_send(attr, mqd, my_mq);
  mq_receive(attr, mqd, my_mq);

  /* code */
  print();
  return 0;
}

int print() {
  int x;
  for (int i = 0; buf_rec[i]; i++) {

    if (buf_rec[i] == 20) {
      x++;
    } else if (i > 0) {
      x++;
    }
  }
  printf("Your message is: %s\n", buf_rec);
  printf("The wordes you have in the file is%d\n", "[", x, "]");
  return 0;
}