//William Decker

#include <stdio.h>
#include <pthread.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>

#define DEBUG 1

void *div_by_number(void*);

int main(void){
  pthread_t thread_one;
  pthread_t thread_two;
  int status = 0;

  printf("Parent is creating the first child now.\n");
  status = pthread_create(&thread_one, NULL, *div_by_number, (void *) 1);
  if(status != 0){
    printf("Oops, pthread create errored! Code : %d\n", status);
    exit(-1);
  }

  printf("Parent is creating the second child now.\n");
  status = pthread_create(&thread_two, NULL, *div_by_number, (void *) 2);
  if(status != 0){
    printf("Oops, pthread create errored! Code : %d\n", status);
    exit(-1);
  }

  printf("Parent is waiting on the first child to exit.\n");
  printf("Test\n");
  status = pthread_join(thread_one, NULL);
  printf("Test2\n");
  printf("First child has exited, and been joined.\n*");
  printf("Parent is waiting on the second child to exit.\n");
  status = pthread_join(thread_two, NULL);
  printf("Second child has exited and has been joined.\n");

  exit(0);
}

void *div_by_number(void *thread_num){
  int dividend = 84;
  int result = 0;
  int maximum_time = 0;
  int number = 0;

  srandom((unsigned int)time(NULL) + *(int *)thread_num);
  maximum_time = 4;
  number = random() % maximum_time;
  printf("Thread %d sleeping %d seconds.\n", *(int *)thread_num, number);
  sleep(number);

  if(*(int *)thread_num == 1){
    printf("I am the first child, attempting division!\n");
  }

  else{
    printf("I am the second child, attempting division.\n");
  }

  if(*(int *)thread_num == 1){
    result = dividend/2;
  }

  else {
    result = dividend/0;
  }

  if (*(int *)thread_num ==2){
    printf("Problem! Second child should not be here!\n");
    printf("Second child exittting\n");
  }
  else{
    printf("The first child gets a result of %d.\n", result);
    printf("First child exittting\n");
  }

  pthread_exit(NULL);
}
