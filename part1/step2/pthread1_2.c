#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>


pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_barrier_t barrier;

int SharedVariable = 0;

void *SimpleThread(void* which)
{
	long int tid;
	tid = (long int)which;
	int num, val;
	for(num = 0; num < 20; num++)
	{
#ifdef PHTHREAD_SYNC
		if(random() > RAND_MAX/2)
			usleep(10);
#endif
		pthread_mutex_lock(&mutex);
		val = SharedVariable;
		printf("*** thread %ld sees value %d\n",tid, val);
		SharedVariable = val + 1;
		pthread_mutex_unlock(&mutex);
	}
	pthread_barrier_wait(&barrier);

	val = SharedVariable;
	printf("Thread %ld see final value %d\n", tid, val);
}

int main(int argc, char *argv[])
{
	int num_t, i;
	int rc;
	char str[50];
	if(argc <2)
	{
		printf("Invalid number of commands /thread [num]\n");
		exit(1);
	}
	strcpy(str, argv[1]);
	
	int length = strlen(str);

	for(i = 0; i < length; i++ )
	{
		if(!isdigit(argv[1][i]))
		{
			printf("Error, numbers only for thread count\n");
				printf("ex: /thread [num]");
			exit(-1);
		}
		
	}
	printf("Success!\n");

           num_t = atoi(argv[1]);
	if(num_t < 0)
	{
	   printf("Error; parameter should be positive number");
	   exit(-1);

	}
	rc = pthread_barrier_init(&barrier, NULL, num_t);
	
	printf("from commandline: %d\n", argc);

	long int j;
	pthread_t tid[num_t];
	for(j =0; j<num_t ; j++)
	{ 
	    	
	  pthread_create(&tid[j], NULL, SimpleThread, (void *)j);
	     
	}
	
 	for(j = 0; j < num_t; j++)
	{
	   pthread_join(tid[j], NULL);
	}	
	return 0;
}
 
