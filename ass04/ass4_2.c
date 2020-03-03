//Sieve of Eratosthenes algorithm in a divide and conquer paradigm using threads

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

int t=5,n=100; //t==no. of threads and n==the maximum number
int *a,tno=0,i,j;

void *soe(void *val)
{
    int v=tno++;
    int min=(n/t)*v+1;
    min = min < 2 ? 2 : min;
    int max=(n/t)*(v + 1);
    max = max > n ? n : max;

    for(i = min; i <= max && (i * i) <= n; i++)
        for(j = i * i; j <= n; j = j += i)
            a[j] = 1;
}

void main()
{
    a=(int *)malloc((n+1) * sizeof(int));
    for(i=0;i<=n;i++)
    	a[i]=0;

    pthread_t threads[t+1];

    for(i=0;i<=t;i++)
        pthread_create(&threads[i],NULL,soe,NULL);
    for(i=0;i<=t;i++)
    	pthread_join(threads[i],NULL);
    	
    for(i=2;i<=n;i++)
        if(a[i] != 1)
            printf("%d ", i);
    printf("\n");

    pthread_exit(NULL);	

}

