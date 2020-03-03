#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>


#define BUFFER_SIZE 100000
int buffer[BUFFER_SIZE];
int n=0;
int index=0;
sem_t s,delay;
//pthread_mutex_t mutex;

void* produce(void* arg){
	while(1){
		sleep(5);
		int item = rand()%100;
		sem_wait(&s);
		buffer[index++] = item;
		n++;
		printf("Produced- %d\n",item);
		if(n==1)
		sem_post(&delay);
		sem_post(&s);
	}
}

void* consume(void* arg){
	int m;
	sem_wait(&delay);
	while(1){
		sleep(1);
		sem_wait(&s);
		int item = buffer[--index];
		n--;
		m=n;
		printf("Consumed- %d\n",item);
		sem_post(&s);		
		if(m==0)
		sem_wait(&delay);
		

	}
}

int main(){
	pthread_t producer,consumer;
	sem_init(&s,0,1);
	sem_init(&delay,0,0);
	pthread_create(&producer,NULL,produce,NULL);
	pthread_create(&consumer,NULL,consume,NULL);
	pthread_join(producer,NULL);
	pthread_join(consumer,NULL);
	
	
}
