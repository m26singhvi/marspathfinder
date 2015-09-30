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
  
  unsigned int i = 0;
  
  pthread_t id = pthread_self();

  for (i=0; i < (0xFFFFFFFF); i++)
  ;

  if (pthread_equal(id, tid[0]))
  {
    printf("First Thread processing\n ");
  }
  
  return NULL;
}

void* thread_two_function()
{
  printf("Thread 2 started \n");
  
   unsigned int i = 0;
  
  for (i=0; i < (0xFFFFFFFF); i++)
  ;
  return NULL;
}

void* thread_three_function()
{
  printf("Thread 3 started \n");
   unsigned int i = 0;
  for (i=0; i < (0xFFFFFFFF); i++)
  ;
  return NULL;
}

int create_thread(int num, void *func)
{
  int err = 0;
 
   if (func == NULL)
    printf("Thread starting function is null\n");

  err = pthread_create(&(tid[num-1]), NULL, func, NULL);

  if (err != 0)
     printf("Error in creating the thread : %s \n", strerror(err));
  else
     printf("Thread created successfully \n");
  
  return 0;
}
    
int main ()
{
  printf("Hello This is main, I am going to create threads now \n");
  create_thread(1, &thread_one_function);
  create_thread(2, &thread_two_function);
  create_thread(3, &thread_three_function);

  return 0;
}


