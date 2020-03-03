//Readers Writers problem with Readers' priority 

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

int readcount=0,mycount=0; //number of readers
int i;
sem_t wrt;
pthread_mutex_t mutex;
pthread_t writer,reader;

void* reading(void* arg)
{
	while(1)
	{
		sleep(1);
		printf("Reader wants to read !\n");
		pthread_mutex_lock(&mutex);
		readcount++;
		if(readcount==1)
			sem_wait(&wrt);
		mycount++;
		pthread_mutex_unlock(&mutex);
		FILE *fp=fopen("/home/student/Anupam_510817049/Anupam_510817049OS5thSem/Assignment8/Data.csv","r");
		printf("Reading the file -->\n");
		char c;
		//sleep(1);
	    	c = fgetc(fp); 

		while (c != EOF) 
   		{ 
        		printf ("%c ", c); 
        		c = fgetc(fp); 
    		} 
		printf("Reading Completed !\n");
		mycount--;
		pthread_mutex_lock(&mutex);
		readcount--;
		if(readcount==0)
			sem_post(&wrt);
		pthread_mutex_unlock(&mutex);		
	}
}

void* writing(void* arg)
{
	while(1)
	{	
		sleep(1);
		printf("Writer wants to write !\n");
		sem_wait(&wrt);
		printf("mycount=%d\n ",mycount);
		FILE *fp=fopen("/home/student/Anupam_510817049/Anupam_510817049OS5thSem/Assignment8/Data.csv","a");
		printf("Writing-->\n");;
		for(i=0;i<10;i++)
		{
			fprintf(fp,"%d ",i);
			printf("%d ",i);
		}
		printf("\n");
		
		fclose(fp);
		sem_post(&wrt);
	}
}


int main()
{
	sem_init(&wrt,0,1);
	pthread_mutex_init(&mutex,NULL);
	
	for(i=0;i<3;i++)
		pthread_create(&writer,NULL,writing,NULL);
	for(i=0;i<3;i++)
		pthread_create(&reader,NULL,reading,NULL);
	
	pthread_exit(NULL);
}
