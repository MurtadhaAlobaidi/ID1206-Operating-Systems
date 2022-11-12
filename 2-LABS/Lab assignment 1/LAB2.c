#include <dirent.h> /* Handling directory files */
#include <errno.h>  /* EXIT codes and error handling */
#include <fcntl.h>  /* Defines requests/arguments used by mq_open */
#include <mqueue.h> /* Queue functions */
#include <stdio.h>  /* Basic input/output stream */
#include <stdlib.h> /* Standard library */
#include <string.h> /* Size_t, strlen */
#define MAX_SIZE 100
#define MAX_NUM_MSG 10 

/*
int read() {
 
  return r;
}*/

int mq_sender(struct mq_attr attr, mqd_t mqd, char *my_mq){
  
  FILE *file;
  file = fopen("file.txt", "r");
  //char buf[MAX_SIZE]; 
  char *buf = malloc (sizeof *buf*MAX_SIZE);
  size_t s=0;
    int r;

  
  if (!file)
       {
    perror("Error file not open ");
    exit(1);
  }
  while ((r = fgetc(file)) != EOF) {
    buf[s++]= r;
    //printf("%c", r);
  }
  fclose(file);

// Open an existing message queue
mqd = mq_open(my_mq, O_CREAT | O_WRONLY, S_IRUSR | S_IWUSR,&attr);

// Write from "file" to the message queue
mq_send(mqd, buf, strlen(buf), 1);

// Close the message queue
mq_close(mqd);
free(buf); /* free allocated memory */

return 0;
}

int mq_receiveer(struct mq_attr attr, mqd_t mqd,char *my_mq)
{
  
//char buf_rec[MAX_SIZE];
char *buf_rec = malloc (sizeof * buf_rec*MAX_SIZE);

// Create message queue
mqd = mq_open(my_mq, O_RDONLY | O_CREAT, S_IRUSR | S_IWUSR, &attr);

// Read the message from the message queue
mq_receive(mqd, buf_rec, MAX_SIZE, NULL); 
//printf("Message: %s\n", buf);

// Close the message queue
mq_close(mqd);
//removes the message queue identified by name.
mq_unlink(my_mq);

 int x=0;
    for(int i = 0;buf_rec[i]; i++)
    {
        
        if (buf_rec[i] == 50) {
            x++;
        }
        if (i >0) {
        x++;
        }
    }
    printf("Your message is: %s\n", buf_rec);
    printf("The wordes you have in the file is= %d\n", x );
    printf("\n");

}




// struct mq_attr attr(){
// attr mq_flags = 0; // Message queue description flags
// attr mq_maxmsg = MAX_NUM_MSG; // Maximum number of messages on queue
// attr mq_msgsize = MAX_SIZE; // Maximum message size (in bytes)
// attr mq_curmsgs = 0; // Number of messages currently in queue
// };

int main(int argc, char const *argv[])
{
    char *my_mq = "/mymq";  /* queue name */
    mqd_t mqd; // message queue 

    struct mq_attr attr;  /* queue attributes */
    attr.mq_flags = 0; // Message queue description flags
    attr.mq_maxmsg = MAX_NUM_MSG; // Maximum number of messages on queue
    attr.mq_msgsize = MAX_SIZE; // Maximum message size (in bytes)
    attr.mq_curmsgs = 0; // Number of messages currently in queue
    
    //read();

    mq_sender(attr,mqd,my_mq);
    mq_receiveer(attr,mqd,my_mq);

    /* code */
    //print();
}

/*int print(){
 
    return 0;
}*/
