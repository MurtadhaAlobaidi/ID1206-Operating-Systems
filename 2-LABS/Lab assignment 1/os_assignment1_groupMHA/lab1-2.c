#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int MAX_SIZE = 100;
int MAX_NUM_MSG = 10;

/*
 * @mq_sender From our course lecture 02 "Message Queue"
 * @mq_receiveer From our course lecture 02 "Message Queue"
 * */
int mq_sender(struct mq_attr attr, mqd_t mqd, char *my_mq) {

  char *buf;

  FILE *file;
  char filename[] = "text.txt";
  file = fopen(filename, "r");

  /* malloc() method inspiration from
   *"https://www.tutorialspoint.com/c_standard_library/c_function_malloc.htm"
   * The “malloc” or “memory allocation”
   * used to dynamically allocate a single
   *large block of memory with the specified size.
   *It returns a pointer of type void which can be
   *cast into a pointer of any form
   * */
  buf = (char *)malloc(sizeof(char) * MAX_SIZE);
  size_t s = 0;
  int checker;

  while ((checker = fgetc(file)) != EOF) {
    buf[s++] = checker;
  }
  fclose(file);

  // printf("%stest: \n", buf);

  // Open an existing message queue
  mqd = mq_open(my_mq, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR, &attr);

  // Write from "file" to the message queue
  mq_send(mqd, buf, strlen(buf), 0);

  // Close the message queue
  mq_close(mqd);

  /* free allocated memory */
  free(buf);

  return 0;
}

int mq_receiveer(struct mq_attr attr, mqd_t mqd, char *my_mq) {
  char *buf_rec;
  /*
   * malloc() method inspiration from
   *"https://www.tutorialspoint.com/c_standard_library/c_function_malloc.htm"
   * */
  buf_rec = (char *)malloc(sizeof(char) * MAX_SIZE);

  // Create message queue
  mqd = mq_open(my_mq, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR, &attr);

  // Read the message from the message queue
  mq_receive(mqd, buf_rec, MAX_SIZE, NULL);
  // printf("Message: %s\n", buf);

  // Close the message queue
  mq_close(mqd);
  // removes the message queue identified by name.
  mq_unlink(my_mq);

  int nummber_of_worde = 0;

  for (int i = 0; i < MAX_SIZE; i++) {
    // printf("tecken: %d\n", buf_rec[i]);
    if (buf_rec[i] == 32) {
      nummber_of_worde++;
    }

    if (buf_rec[i] == 0) {
      nummber_of_worde++;
      break;
    }
  }
  printf("Your words is: %s\n", buf_rec);
  printf("The number of words is = %d\n", nummber_of_worde);
  printf("\n");
  return 0;
}

void message_queues() {

  char *my_mq = "/mymq"; // queue name
  mqd_t mqd;             // message queue

  struct mq_attr attr;          /* queue attributes */
  attr.mq_flags = 0;            // Message queue description flags
  attr.mq_maxmsg = MAX_NUM_MSG; // Maximum number of messages on queue
  attr.mq_msgsize = MAX_SIZE;   // Maximum message size (in bytes)
  attr.mq_curmsgs = 0;          // Number of messages currently in queue

  mq_sender(attr, mqd, my_mq);
  mq_receiveer(attr, mqd, my_mq);
}

int main() {
  message_queues(); // biuld the message_queues /
}