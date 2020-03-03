//Killing a Zombie Process by using the wait system call

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int pid;
	pid=fork();
	if(pid==0)
		printf("I'm the Child : %d\n",getpid());
	else
	{
		wait(NULL);
		printf("I'm the Parent : %d\n",getppid());
		while(1);
	}
	return 0;
}		
