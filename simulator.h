#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <limits.h>

void * thread_one_function();
void * thread_two_function();
void * thread_three_function();
int create_thread(int num, void *func, pthread_attr_t *attr);
int create_threads();
int init_main();

pthread_t tid[3];
