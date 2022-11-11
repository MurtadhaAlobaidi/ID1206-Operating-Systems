#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/types.h>
#define MAXSIZE 128

/**
 **see the message queue state, by running command
 *"ipcs -q"
 * For your linux system, you can know all the details of the IPC mechanisms and
 *available queues
 * "ipcs -a"
 * From
 *https://stackoverflow.com/questions/3056307/how-do-i-use-mqueue-in-a-c-program-on-a-linux-based-system
 */
void die(char *s) {
  perror(s);
  exit(1);
}

struct msgbuf {
  long mtype;
  char mtext[MAXSIZE];
};

int main() {
  int msqid;
  key_t key;
  struct msgbuf rcvbuffer;

  key = 1234;

  if ((msqid = msgget(key, 0666)) < 0)
    die("msgget()");

  // Receive an answer of message type 1.
  if (msgrcv(msqid, &rcvbuffer, MAXSIZE, 1, 0) < 0)
    die("msgrcv");

  printf("%s\n", rcvbuffer.mtext);
  exit(0);
}