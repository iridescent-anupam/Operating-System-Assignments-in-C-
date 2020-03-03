#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>

long long int factorial(long long int n)
{
	
	if(n==0 || n==1)
		return 1;
	else
		return n*factorial(n-1);
}		

int main(int argc,int *argv[])
{
	fork();
	fork();
	fork();
	fork();

	if(fork() == 0)
	{
		printf("From Child - %lld\n",factorial(argv[1]));
	}
	else
	{
		printf("From Parent - %lld\n",factorial(argv[1]));
	}
	return 0;
}	
	
