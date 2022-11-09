#include <unistd.h>

int main(void) {
  /*****1- execl() System Function: ************/
  char *binaryPath = "/bin/ls";
  char *arg1 = "-lh";
  char *arg2 = "/home";

  execl(binaryPath, binaryPath, arg1, arg2, NULL);
  return 0;
  /********2- execlp() System Function: ********/
  char *programName = "ls";
  char *arg1 = "-lh";
  char *arg2 = "/home";

  execlp(programName, programName, arg1, arg2, NULL);
  return 0;
  /*******3- execv() System Function: ********/
  char *binaryPath = "/bin/ls";
  char *args[] = {binaryPath, "-lh", "/home", NULL};

  execv(binaryPath, args);
  return 0;
  /****4- execvp() System Function: ***********/
  char *programName = "ls";
  char *args[] = {programName, "-lh", "/home", NULL};

  execvp(programName, args);
  return 0;
  /********5- execle() System Function: *********/
  char *binaryPath = "/bin/bash";
  char *arg1 = "-c";
  char *arg2 = "echo " Visit $HOSTNAME : $PORT from your browser."";
  char *const env[] = {"HOSTNAME=www.linuxhint.com", "PORT=8080", NULL};

  execle(binaryPath, binaryPath, arg1, arg2, NULL, env);
  return 0;
  /*****6- execve() System Function: *********/
  char *binaryPath = "/bin/bash";
  char *const args[] = {
    binaryPath,
    "-c",
    "echo " Visit $HOSTNAME : $PORT from your browser."",
    NULL
  };
  char *const env[] = {"HOSTNAME=www.linuxhint.com", "PORT=8080", NULL};

  execve(binaryPath, args, env);
  return 0;
  ///*******https://linuxhint.com/exec_linux_system_call_c/ *****/
}