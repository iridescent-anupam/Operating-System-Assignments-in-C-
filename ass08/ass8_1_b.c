#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

#define PROD_DELAY 1000		// in microseconds
#define CONS_DELAY 1000		// in microseconds

int buf_items; // implementing unbounded buffer
pthread_mutex_t mutex;
pthread_cond_t non_zero_item;

void* producer(void* arg)
{
	while(1)
	{
		usleep(PROD_DELAY);

		pthread_mutex_lock(&mutex);
		printf("Before producer production: %d\n", buf_items);
		++buf_items;
		printf("After producer production: %d\n", buf_items);
		pthread_cond_signal(&non_zero_item);
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

void* consumer(void* arg)
{
	while(1)
	{
		usleep(CONS_DELAY);

		#ifdef BAD_DESIGN
			// A condition variable must always be associated 
			// with a mutex, to avoid the race condition where 
			// a thread prepares to wait on a condition variable 
			// and another thread signals the condition just 
			// before the first thread actually waits on it.

			while(buf_items == 0);	// bad_design
		#endif
		
		pthread_mutex_lock(&mutex);
		while(buf_items == 0)
			pthread_cond_wait(&non_zero_item, &mutex);
		printf("Before consumer consumption: %d\n",buf_items);
		--buf_items;
		printf("After consumer consumption: %d\n", buf_items);
		pthread_mutex_unlock(&mutex);
	}

	return NULL;
}

int main(int argc, char *argv[])
{	
	pthread_t prod, cons;
	pthread_attr_t attr;
	pthread_attr_init(&attr);

	pthread_create(&prod, &attr, producer, NULL);
	pthread_create(&cons, &attr, consumer, NULL);

	pthread_join(prod, NULL);
	pthread_join(cons, NULL);

	return 0;
}
