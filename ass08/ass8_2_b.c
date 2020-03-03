//Readers Writers problem with Writers' priority 

#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <stdlib.h>
#include <unistd.h>

int readcount=0;
int i,AR=0,AW=0,WW=0,WR=0;
sem_t oktoread,oktowrite;
pthread_mutex_t mutex;
pthread_t writer,reader;

void* reading(void* arg)
{
	while(1)
	{	
		printf("Reader wants to read !\n");
		pthread_mutex_lock(&mutex);
		if(AW+WW>0)
			WR++;		
		else
		{
			sem_post(&oktoread);
			AR++;
		}
		pthread_mutex_unlock(&mutex);
		sem_wait(&oktoread);
		FILE * fp=fopen("/home/student/Anupam_510817049/Anupam_510817049OS5thSem/Assignment8/Data2.csv","r");
		printf("Reading-->\n");
		char c;
		//sleep(1);
	    	c = fgetc(fp); 

		while (c != EOF) 
   		{ 
        		printf ("%c ", c); 
        		c = fgetc(fp); 
    		}
		pthread_mutex_lock(&mutex);
		AR--;
		if(AR==0&&WW>0)
		{
			sem_post(&oktowrite);
			AW++;
			WW--;
		}
		pthread_mutex_unlock(&mutex);
	}
}


void* writing(void* arg)
{
	while(1)
	{
		printf("Writer wants to write !\n");
		pthread_mutex_lock(&mutex);
		if(AW+AR>0)
			WW++;		
		else
		{
			sem_post(&oktowrite);
			AW++;
		}
		
		pthread_mutex_unlock(&mutex);
		sem_wait(&oktowrite);
		FILE * fp=fopen("/home/student/Anupam_510817049/Anupam_510817049OS5thSem/Assignment8/Data2.csv","a");
		printf("Writing-->\n");
		printf("Active readers : %d %d\n",AR,WR);
		
		sleep(1);
		for( i=0;i<10;i++)
		{
			fprintf(fp,"%d ",i);
			printf("%d ",i);
		}
		printf("\n");
		pthread_mutex_lock(&mutex);
		
		sleep(20);
		AW--;
		if(WW>0)
		{
			sem_post(&oktowrite);
			AW++;
			WW--;
		}
		else
		{
			sem_post(&oktoread);
			AR++;
			WR--;
		}
		pthread_mutex_unlock(&mutex);		
	}
	
}

int main()
{
	sem_init(&oktoread,0,0);
	sem_init(&oktowrite,0,0);	
	
	pthread_mutex_init(&mutex,NULL);
	
	for(i=0;i<3;i++)	
		pthread_create(&writer,NULL,writing,NULL);
	for(i=0;i<3;i++)
		pthread_create(&reader,NULL,reading,NULL);
	
	pthread_exit(NULL);
	return 0;
}
