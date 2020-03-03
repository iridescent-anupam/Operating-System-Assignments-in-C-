//Creates 2 threads. One of these prints all the odd numbers from 1 to N, the other prints all the even numbers from 1 to N. After the 2 threads terminate, the sum of all the integers from 1 to N should be computed by adding the sum of odd numbers and Sthe sum of even numbers.

#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/wait.h>
#include<unistd.h>

int N,sum,sum1,sum2;

void *even(void *vargp)
{
	int i,sum1=0;
	for(i=2;i<N;i=i+2)
	{
		printf("%d ",i);
		sum1=sum1+i;
	}	
	return *(&sum1);
}

void *odd(void *vargp)
{
	int i,sum2=0;
	for(i=1;i<N;i=i+2)
	{
		printf("%d ",i);
		sum2=sum2+i;
	}	
	printf("\n");	
	return *(&sum2);		
}	
	
int main()
{
    printf("Enter the value of N : ");
    scanf("%d",&N);
    pthread_t thread1, thread2; 
    // create threads
    pthread_create(&thread1, NULL, odd, (void*)&N);
    pthread_create(&thread2, NULL, even, (void*)&N);
    // wait for threads to finish their work
    pthread_join(thread1, (void**)&sum1);
    pthread_join(thread2, (void**)&sum2);
    sum=sum1+sum2;
    printf("\nThe sum is : %d\n",sum);
    return 0;
}
			
