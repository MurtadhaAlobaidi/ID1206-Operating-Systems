#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * LAB 4*/
int cylinder[5000];
int series[1000];
int head;

/**
 * @FCFS We take th #head as input from the Cylinder rang and
 * wi will go through all the #queue
 * And we calculate the sam of all the steps (Total head movement cylinders) */
int FCFS() {
  int steps = 0;
  int pointer = head;
  for (int i = 0; i < 8; i++) {

    steps += abs(pointer - series[i]);

    pointer = series[i];
  }
  return steps;
}
/**
@SSTF the #head as input from argument */
int SSTF() {
  int visted[8];
  int steps = 0;
  int pointer = head;
  for (int i = 0; i < 8; i++) {
    visted[i] = 0;
  }

  int min = 5000;
  int index = 0;
  for (int i = 0; i < 8; i++) {

    for (int j = 0; j < 8; j++) {
      if (visted[j] != 1 && (abs(pointer - series[j]) < min)) {
        min = abs(pointer - series[j]);
        index = j;
      }
    }

    steps += min;
    pointer = series[index];
    visted[index] = 1;
    min = 5000;
  }

  return steps;
}

/*SCAN the #head as input from argument
 * */
int SCAN() {
  int pointer = head;

  int steps = 0;
  int maxToMinIndex = 0;
  int minToMaxIndex = 0;

  int max = -5000;
  int min = 5000;
  int index = 0;
  for (int i = 0; i < 8; i++) {
    max = series[i];
    if (series[i] <= head) {
      minToMaxIndex++;
    } else {
      maxToMinIndex++;
    }

    for (int j = i + 1; j < 8; j++) {
      if (series[j] >= max) {
        max = series[j];
        index = j;
      }
    }
    int x = series[i];
    series[i] = series[index];
    series[index] = x;
  }

  for (int i = 8 - 1; i >= minToMaxIndex; i--) {
    steps += abs(pointer - series[i]);
    pointer = series[i];
  }
  steps += abs(pointer - 0);
  pointer = 0;
  for (int i = minToMaxIndex - 1; i >= 0; i--) {
    steps += abs(pointer - series[i]);
    pointer = series[i];
  }

  return steps;
}
/*C-SCAN the #head as input from argument*/
int CSCAN() {
  int pointer = head;

  int steps = 0;
  int maxToMinIndex = 0;
  int minToMaxIndex = 0;

  int max = -5000;
  int min = 5000;
  int index = 0;
  for (int i = 0; i < 8; i++) {
    max = series[i];
    if (series[i] <= head) {
      minToMaxIndex++;
    } else {
      maxToMinIndex++;
    }

    for (int j = i + 1; j < 8; j++) {
      if (series[j] >= max) {
        max = series[j];
        index = j;
      }
    }
    int x = series[i];
    series[i] = series[index];
    series[index] = x;
  }

  for (int i = minToMaxIndex - 1; i >= 0; i--) {
    steps += abs(pointer - series[i]);
    pointer = series[i];
  }

  steps += abs(pointer - 199);
  pointer = 199;

  steps += abs(pointer - 0);
  pointer = 0;
  for (int i = minToMaxIndex; i < 8; i++) {
    steps += abs(pointer - series[i]);
    pointer = series[i];
  }

  return steps;
}
/*LOOK the #head as input from argument*/
int LOOK() {
  int pointer = head;

  int steps = 0;
  int maxToMinIndex = 0;
  int minToMaxIndex = 0;

  int max = -5000;
  int min = 5000;
  int index = 0;
  for (int i = 0; i < 8; i++) {
    max = series[i];
    if (series[i] <= head) {
      minToMaxIndex++;
    } else {
      maxToMinIndex++;
    }

    for (int j = i + 1; j < 8; j++) {
      if (series[j] >= max) {
        max = series[j];
        index = j;
      }
    }
    int x = series[i];
    series[i] = series[index];
    series[index] = x;
  }

  for (int i = 8 - 1; i >= minToMaxIndex; i--) {
    steps += abs(pointer - series[i]);
    pointer = series[i];
  }
  for (int i = minToMaxIndex - 1; i >= 0; i--) {
    steps += abs(pointer - series[i]);
    pointer = series[i];
  }

  return steps;
}
/*C-LOOK the #head as input from argument*/
int CLOOK() {

  int pointer = head;

  int steps = 0;
  int maxToMinIndex = 0;
  int minToMaxIndex = 0;

  int max = -5000;
  int min = 5000;
  int index = 0;
  for (int i = 0; i < 8; i++) {
    max = series[i];
    if (series[i] <= head) {
      minToMaxIndex++;
    } else {
      maxToMinIndex++;
    }

    for (int j = i + 1; j < 8; j++) {
      if (series[j] >= max) {
        max = series[j];
        index = j;
      }
    }
    int x = series[i];
    series[i] = series[index];
    series[index] = x;
  }

  for (int i = minToMaxIndex - 1; i >= 0; i--) {
    steps += abs(pointer - series[i]);
    pointer = series[i];
  }

  for (int i = minToMaxIndex; i < 8; i++) {
    steps += abs(pointer - series[i]);
    pointer = series[i];
  }

  return steps;
}

int main(int argc, char *argv[]) {

  if (argc < 2) {
    printf("There are no argument.\n");
    return 0;
  }

  head = atoi(argv[1]);
  for (int i = 0; i < 1000; i++) {
    series[i] = rand() % 5000;
  }

  /* FCFS */
  int x = FCFS();
  printf("FCFS Total head movement: %d cylinder\n", x);

  /* SSTF */
  int x2 = SSTF();
  printf("SSTF Total head movement: %d cylinder\n", x2);

  /* SCAN */
  int x3 = SCAN();
  printf("SCAN Total head movement: %d cylinder\n", x3);

  /*C-SCAN*/
  int x4 = CSCAN();
  printf("CSCAN Total head movement: %d cylinder\n", x4);

  /*LOOK*/
  int x5 = LOOK();
  printf("LOOK Total head movement: %d cylinder\n", x5);

  /*C-LOOK*/
  int x6 = CLOOK();
  printf("C-LOOK Total head movement: %d cylinder\n", x6);

  return 0;
}
