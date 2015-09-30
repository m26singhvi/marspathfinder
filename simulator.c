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
  pthread_t id = pthread_self();
  setAffinity(id);
  
  unsigned int i = 0;
  int policy;
  int ret;

  sched_getparam(0, &param);
  printf("Priority for thread 1 = %d \n", param.sched_priority);
  
  sleep(10);
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
  pthread_t id = pthread_self();
  setAffinity(id);
  sleep(10);
  
   unsigned int i = 0;
  
  for (i=0; i < (0xFFFFFFFF); i++)
  ;
  if (pthread_equal(id, tid[1]))
  {
    printf("Second Thread processing\n ");
  }

  return NULL;
}

void* thread_three_function()
{
  printf("Thread 3 started \n");
  pthread_t id = pthread_self();
  setAffinity(id);
  sleep(10);
  int i = 0;
  
  for (i=0; i < (0xFFFFFFFF); i++)
  ;

  if (pthread_equal(id, tid[2]))
  {
    printf("Third Thread processing\n ");
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
     return err;
  else
     printf("Thread created successfully : %s \n", strerror(err));
  
  return 0;
}

int setAffinity(pthread_t id)
{
  cpu_set_t mask;
  CPU_ZERO(&mask);
  
  CPU_SET(0, &mask);
  pthread_setaffinity_np(id, sizeof(cpu_set_t), &mask);

}

int create_threads()
{
  printf("Creating threads now \n");
  
  int err = 0;
  pthread_attr_t attr;
  int ret;
  int i;

  ret = pthread_attr_init(&attr);
   
  struct sched_param param;
  pthread_attr_setschedpolicy(&attr, SCHED_FIFO);
  param.sched_priority = 40;
  pthread_attr_setschedparam(&attr, &param);

  ret = create_thread(1, &thread_one_function, &attr);
  if (ret == -1)
    printf(" Creating Thread : %s Error\n", __func__);
  param.sched_priority = 30;
  ret = pthread_attr_setschedparam(&attr, &param);
  if (ret == -1)
    printf("Setting Param : %s Error\n", __func__);
  ret = create_thread(2, &thread_two_function, &attr);
  if (ret == -1)
    printf("Creating thread :  %s Error\n", __func__);
  param.sched_priority = 20;
  ret = pthread_attr_setschedparam(&attr, &param);
  if (ret == -1)
    printf("Setting Param  %s Error\n", __func__);
  ret = create_thread(3, &thread_three_function, &attr);
  if (ret == -1)
    printf("Creating Thread :  %s Error\n", __func__);
  
  for(i = 0; i < 3; i++)
   pthread_join(tid[i], NULL);

  return 0;

}


  
int main ()
{
  int ret;
  int i;
  struct sched_param param;
  int policy;
  param.sched_priority = 90;
  policy = SCHED_FIFO;
  ret = pthread_setschedparam(0, policy, &param);
  pthread_getschedparam(0, &policy, &param);
  printf("Set Priority : Main %d \n", param.sched_priority);
  create_threads();
  
  while(1)
  printf("I am in main \n");

  return 0;
}


