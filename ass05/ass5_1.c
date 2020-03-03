#define _GNU_SOURCE
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>

int odds=0,evens=0,n=100;

void *odd(void *vargp)
{
	printf("1-%ld\n",pthread_self());
	printf("1-Inside the thread\n");
	pthread_t tid = pthread_self();
	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);

	CPU_SET(0, &cpuset);
	pthread_setaffinity_np(tid, sizeof(cpu_set_t), &cpuset);
	int i;
	for(i=1;i<=n;i++)
	{
		if(i%2==1)
		{
			odds+=i;
			printf("even-%d\n",i);
		}
	}
	return NULL;
}


void *even(void *vargp)
{
	printf("2-%ld\n",pthread_self());
	printf("2-Inside the thread\n");
	pthread_t tid = pthread_self();
	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);

	CPU_SET(1, &cpuset);
	pthread_setaffinity_np(tid, sizeof(cpu_set_t), &cpuset);
	int i;
	for(i=1;i<=n;i++)
	{
		if(i%2==0)
		{
			evens+=i;
			printf("odd-%d\n",i);
		}

	}
	return NULL;
}


int main()
{
	pthread_t tid1, tid2, tid3, tid4, tid5;
	printf("Before thread\n");
	pthread_create(&tid1, NULL, odd, NULL);
	pthread_create(&tid2, NULL, even, NULL);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	printf("After thread\n");
	exit(0);
}

