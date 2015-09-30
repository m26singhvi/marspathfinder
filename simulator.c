#define _GNU_SOURCE
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <limits.h>
#include <string.h>
#include "simulator.h"
#include <sched.h>

void* thread_one_function()
{
  printf("Thread 1 started \n");
  struct sched_param param;
   
  int policy;
  pthread_getschedparam(pthread_self(), &policy, &param);
  printf("%d \n", policy);
  policy = SCHED_FIFO;
  printf("%d \n", policy);
  param.sched_priority = 9;
  int ret = pthread_setschedparam(pthread_self(), policy, &param);

  if (ret == -1)
  printf("Error");

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
  struct sched_param param;
  int policy;
  pthread_getschedparam(pthread_self(), &policy, &param);
  printf("%d \n", policy);
  param.sched_priority = 9;
  int ret = pthread_setschedparam(pthread_self(), policy, &param);
  pthread_t id = pthread_self();
  
   unsigned int i = 0;
  
  for (i=0; i < (0xFFFFFFFF); i++)
  ;
  if (pthread_equal(id, tid[0]))
  {
    printf("Second Thread processing\n ");
  }

  return NULL;
}

void* thread_three_function()
{
  printf("Thread 3 started \n");
  struct sched_param param;
  int policy;
  pthread_getschedparam(pthread_self(), &policy, &param);
  printf("%d \n", policy);
  param.sched_priority = 9;
  int ret = pthread_setschedparam(pthread_self(), policy, &param);
   unsigned int i = 0;
  pthread_t id = pthread_self();
  for (i=0; i < (0xFFFFFFFF); i++)
  ;

  if (pthread_equal(id, tid[0]))
  {
    printf("Second Thread processing\n ");
  }
  return NULL;
}

int create_thread(int num, void *func, pthread_attr_t *attr)
{
  int err = 0;
  if (func == NULL)
   printf("Thread starting function is null\n");

  err = pthread_create(&(tid[num-1]), attr, func, NULL);

  if (err != 0)
     printf("Error in creating the thread : %s \n", strerror(err));
  else
     printf("Thread created successfully : %s \n", strerror(err));
  
  return 0;
}

int create_threads()
{
  int err = 0;
  pthread_attr_t attr;
  int ret;

  ret = pthread_attr_init(&attr);
  cpu_set_t mask;
  CPU_ZERO(&mask);
  
  CPU_SET(0, &mask);
  pthread_attr_setaffinity_np(&attr, sizeof(cpu_set_t), &mask);
   
  ret = create_thread(1, &thread_one_function, &attr);
  ret = create_thread(2, &thread_two_function, &attr);
  ret = create_thread(3, &thread_three_function, &attr);
  
  return 0;

}


  
int main ()
{
  int ret;
  int i;
  struct sched_param param;
  int policy;
  pthread_getschedparam(pthread_self(), &policy, &param);
  printf("%d \n", policy);
  policy = SCHED_FIFO;
  printf("%d \n", policy);
  param.sched_priority = 99;
  ret = pthread_setschedparam(pthread_self(), policy, &param);
  

  printf("Hello This is main, I am going to create threads now \n");
 create_threads();
  //create_thread(1, &thread_one_function);
  //create_thread(2, &thread_two_function);
  //create_thread(3, &thread_three_function);

  for(i = 0; i < 3; i++)
   pthread_join(tid[1], NULL);

  return 0;
}


