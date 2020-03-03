//program which creates 2 threads T1 and T2. Thread Ti should add i repeatedly to a shared global variable x. All threads should run until x exceeds an upper limit M (done by Peterson's Algorithm)
#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdbool.h>

int M=100;
bool flag[]={1,1};
int turn=0,x=0;

void *p1()
{
	while(1)
	{
		if (x > M)
			break;
		flag[0]=1;
		turn=1;
		
		while(flag[1] && (turn==1));
		
		printf("Thread 1 %d\n",x);    
		x+=1;

		flag[0]=0;
	}		
		
}

void *p2()
{
	while(1)
	{
		if (x > M)
			break;
		flag[1]=1;
		turn=0;
		
		while(flag[1] && (turn==0));
		
		printf("Thread 2 %d\n",x);
		x+=2;

		flag[1]=0;
	}		
}



int main() {
	
	pthread_t tid1,tid2;
	pthread_create(&tid1,NULL,p1,NULL);
	pthread_create(&tid2,NULL,p2,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	return 0;
}

			
