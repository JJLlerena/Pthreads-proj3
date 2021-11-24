#include <stdio.h>
#include <pthread.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

//initializing mutex
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
//initializing barrier
pthread_barrier_t barrier;

int SharedVariable = 0;

//Given code modified to include barrier/mutex
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
    //validationg command line argument count
	if(argc <2)
	{
		printf("Invalid number of commands /thread [num]\n");
		exit(1);
	}
	strcpy(str, argv[1]);
	
	int length = strlen(str);

    //checking command line for int argument only
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
    //validating for umbers only on commandline input
	if(num_t < 0)
	{
	   printf("Error; parameter should be positive number");
	   exit(-1);

	}
	//barrier declaration
	rc = pthread_barrier_init(&barrier, NULL, num_t);
	
	printf("from commandline: %d\n", argc);

	long int j;
	pthread_t tid[num_t];
    //creating threads
	for(j =0; j<num_t ; j++)
	{ 
	    	
	  pthread_create(&tid[j], NULL, SimpleThread, (void *)j);
	     
	}
	//closing threads
 	for(j = 0; j < num_t; j++)
	{
	   pthread_join(tid[j], NULL);
	}
	detstroy
	return 0;
}
 
