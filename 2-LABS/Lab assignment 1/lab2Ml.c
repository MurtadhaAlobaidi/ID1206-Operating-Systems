#include <dirent.h> //files
#include <errno.h>  /* error handling */
#include <fcntl.h>  // mq_open
#include <fcntl.h>
#include <mqueue.h> /* Queue functions */
#include <stdio.h>  //input and output
#include <stdlib.h> // library
#include <string.h> //Size_t  and strlen
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <sys/types.h>

int sender_process(struct mq_attr attributes, mqd_t mqd, char *my_mq) {

  FILE *fp = fopen("text.txt", "r");
  char *read_buffer = malloc(sizeof *read_buffer * MAX_SIZE);
  size_t size = 0;
  int c;

  if (!fp) { /* validate file open for reading */
    fprintf(stderr, "error: file open failed");
    return 1;
  }

  if (!read_buffer) { /* validate memory allocation succeeded */
    fprintf(stderr, "error: virtual memory exhausted.\n");
    return 1;
  }

  while ((c = fgetc(fp)) != EOF) {
    read_buffer[size++] = c;
  }

  if (fp != stdin)
    fclose(fp); /* close file if not stdin */

  /**SENDING**/
  mqd = mq_open(my_mq, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR, &attributes);
  if (mqd == -1) {
    printf("Failed to create queue.\n");
    return 1;
  }
  mq_send(mqd, read_buffer, strlen(read_buffer), 1);
  mq_close(mqd);
  free(read_buffer); /* free allocated memory */

  return 0;
}

/**
 * @brief starts a process and receives the sent queue and then counts the word
 * inside of it.
 *
 * @param attributes the attributes for the queue
 * @param mqd message queue descriptor
 * @param my_mq the name of the queue
 * @return int
 */
int receiver_process(struct mq_attr attributes, mqd_t mqd, char *my_mq) {

  char *buffer = malloc(sizeof *buffer * MAX_SIZE);
  int i, words = 0;

  /**RECIEVING**/
  mqd = mq_open(my_mq, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR, &attributes);
  mq_receive(mqd, buffer, MAX_SIZE, NULL);
  mq_close(mqd);

  mq_unlink(my_mq); /* delete queue */

  for (i = 0; buffer[i]; i++) {
    if (buffer[i] == 32)
      words++;
  }

  if (i > 0) {
    words++;
  }

  printf("The text: %s\n", buffer);
  printf("Number of words in the file = %d\n", words);

  return 0;
}

void main() {

  char *my_mq = "/mymq"; /* queue name */
  mqd_t mqd;             /* message queue descriptor */

  /* Form the queue attributes */
  struct mq_attr attributes;
  attributes.mq_maxmsg = MAX_NUM_MSG;
  attributes.mq_msgsize = MAX_SIZE;
  attributes.mq_flags = 0;
  attributes.mq_curmsgs = 0;

  sender_process(attributes, mqd, my_mq);
  receiver_process(attributes, mqd, my_mq);
}
