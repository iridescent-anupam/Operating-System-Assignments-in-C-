#define _GNU_SOURCE
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>
#define N 4
 
int res[N][N];  
int mat1[N][N] = {{1, 1, 1, 1},
                  {2, 2, 2, 2},
                  {3, 3, 3, 3},
                  {4, 4, 4, 4}};
 
int mat2[N][N] = {{1, 1, 1, 1},
                  {2, 2, 2, 2},
                  {3, 3, 3, 3},
                  {4, 4, 4, 4}};


void *multiply1(void *vargp)
{
	pthread_t tid = pthread_self();
	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);

	CPU_SET(0, &cpuset);
	pthread_setaffinity_np(tid, sizeof(cpu_set_t), &cpuset);
    	int i, j, k;
    	for (i = 0; i < 1; i++)
    	{
        	for (j = 0; j < N; j++)
        	{
            		res[i][j] = 0;
           		for (k = 0; k < N; k++)
                	res[i][j] += mat1[i][k] * mat2[k][j];
        	}
    	}
}


void *multiply2(void *vargp)
{
	pthread_t tid = pthread_self();
	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);

	CPU_SET(1, &cpuset);
	pthread_setaffinity_np(tid, sizeof(cpu_set_t), &cpuset);
   	int i, j, k;
    	for (i = 1; i < 2; i++)
    	{
        	for (j = 0; j < N; j++)
        	{
            		res[i][j] = 0;
            		for (k = 0; k < N; k++)
                	res[i][j] += mat1[i][k] * mat2[k][j];
        	}
    	}
}


void *multiply3(void *vargp)
{
	pthread_t tid = pthread_self();
	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);

	CPU_SET(2, &cpuset);
	pthread_setaffinity_np(tid, sizeof(cpu_set_t), &cpuset);
    	int i, j, k;
    	for (i = 2; i < 3; i++)
    	{
        	for (j = 0; j < N; j++)
        	{
            		res[i][j] = 0;
            		for (k = 0; k < N; k++)
                	res[i][j] += mat1[i][k] * mat2[k][j];
        	}
    	}
}


void *multiply4(void *vargp)
{
	pthread_t tid = pthread_self();
	cpu_set_t cpuset;

	CPU_ZERO(&cpuset);

	CPU_SET(0, &cpuset);
	pthread_setaffinity_np(tid, sizeof(cpu_set_t), &cpuset);
    	int i, j, k;
    	for (i = 3; i < 4; i++)
    	{
        	for (j = 0; j < N; j++)
        	{
            		res[i][j] = 0;
            		for (k = 0; k < N; k++)
                	res[i][j] += mat1[i][k] * mat2[k][j];
        	}
    	}
}


int main()
{
	pthread_t tid1, tid2, tid3, tid4, tid5;
	int t=clock();
	pthread_create(&tid3, NULL,multiply3 , NULL);
	pthread_create(&tid1, NULL,multiply1, NULL);
	pthread_create(&tid2, NULL,multiply2 , NULL);
	pthread_create(&tid4, NULL,multiply4 , NULL);
	pthread_join(tid3,NULL);
	pthread_join(tid1,NULL);
	pthread_join(tid2,NULL);
	pthread_join(tid4,NULL);
	t=clock()-t;
	int i,j;
	for(i=0;i<4;i++)
	{
		for(j=0;j<4;j++)
		printf("%d ",res[i][j]);
		printf("\n");
	}
	printf("Time taken is-%d\n",t );
}
