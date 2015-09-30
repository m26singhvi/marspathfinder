#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <limits.h>
#include <string.h>
#include "simulator.h"

void* thread_one_function()
{
  printf("Thread 1 started \n");
  return NULL;
}

void* thread_two_function()
{
  printf("Thread 2 started \n");
  return NULL;
}

void* thread_three_function()
{
  printf("Thread 1 started \n");
  return NULL;
}

int create_thread(int num, void *func)
{
  int err = 0;
 
  err = pthread_create(&(tid[num-1]), NULL, func, NULL);

  if (err != 0)
     printf("Error in creating the thread : %s \n", strerror(err));
  else
     printf("Thread created successfully \n");
  
  return 0;
}
    
int main ()
{
  printf("Hello This is the main thread , I am going to create three threads now \n");
  create_thread(1, &thread_one_function);

  return 0;
}


