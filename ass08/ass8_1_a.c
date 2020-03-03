#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h>
#include<semaphore.h>
#include<pthread.h>
#define BUFFER_SIZE 10

int BUFFER[BUFFER_SIZE]; //Buffer
int counter; //Buffer Counter
sem_t full,empty; //Semaphores
pthread_mutex_t mutex; //mutex lock
pthread_t pid,cid;  //Thread IDs
//pthread_attr_t attr; //Set of thread attributes

void *producer(void *arg)
{
	while(1)
	{
		sleep(1);
		sem_wait(&empty);  //Acquire the empty lock
		pthread_mutex_lock(&mutex);  //Acquire the mutex lock
		
		int item = rand()%BUFFER_SIZE;
		BUFFER[counter++] = item;
		printf("Producer produced : %d\n",item);
		
		pthread_mutex_unlock(&mutex);  //Release the mutex lock
		sem_post(&full);  //Signal being full
	}
}	

void *consumer(void *arg)
{
	while(1)
	{
		sleep(1);
		sem_wait(&full);  //Acquire the full lock
		pthread_mutex_lock(&mutex);  //Acquire the mutex lock
		
		int item = BUFFER[--counter];
		printf("Consumer consumed : %d\n",item);
		
		pthread_mutex_unlock(&mutex);  //Release the mutex lock
		sem_post(&empty);  //Signal being empty
	}
}



int main()
{
	pthread_mutex_init(&mutex, NULL); //creating Mutex lock
   	sem_init(&full,0,0); //Create the full semaphore and initialize to 0
   	sem_init(&empty,0,BUFFER_SIZE); //Create the empty semaphore and initialize to BUFFER_SIZE
  	// pthread_attr_init(&attr); //Get the default attributes
  	counter = 0; //init buffer
   
  	pthread_create(&pid,NULL,producer,NULL);
   	pthread_create(&cid,NULL,consumer,NULL);

  	pthread_join(pid,NULL);
  	pthread_join(cid,NULL);
   	
   	sem_destroy(&empty);
   	sem_destroy(&full);
   	pthread_exit(NULL);
   	return 0;
}	
