
#include <pthread.h>

#include <stdio.h>

#include <stdlib.h>

pthread_mutex_t mutex;

int fib[10]; /* this data is shared by the thread(s) */

int in = 0;
long int sum = 0;

void *genFibo(void *param); /* the thread */

int main(int argc, char *argv[])

{
 long int i;
   pthread_attr_t attr;
   //checking for command line input
   if (argc != 2) {

   fprintf(stderr,"usage: ./fibonacci <integer value>\n");

   return -1;

   }

   int count = atoi(argv[1]);
   //checking command line if empty
   if (count < 1) {

   fprintf(stderr,"%d must be>= 1\n", count);

   return -1;

   }

   pthread_attr_init(&attr);

   // Mutex Lock

   pthread_mutex_init(&mutex, NULL);

   // each thread computes fibonacci

   for(i = 1;i <= count;i++) {

   pthread_t thread;

   pthread_create(&thread, &attr, genFibo, (void*)i);

   pthread_join(thread, NULL);

   }

   // print resulting array

   for (i = 0; i < in;i++) {

   printf("%d ", fib[i]);

   }

   printf("\n");

   pthread_mutex_destroy(&mutex);

}
//thread intstructions
void *genFibo(void *param)

{

   pthread_mutex_lock(&mutex);

   fib[in++] = fibonacci((long int)param);

   pthread_mutex_unlock(&mutex);

   sum = sum + fibonacci((long int)param);
   pthread_exit(0);

}
//fibonacci algorithm function
int fibonacci (int x)
{

   if (x <= 1) {

   return 1;

   }

   return fibonacci(x-1) + fibonacci(x-2);

}
