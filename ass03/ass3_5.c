//Killing a Zombie Process by using a Signal Handler

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h> 
#include<sys/types.h>

void function()
{
	wait(NULL);
}	

int main()
{
	if(!fork())
		printf("I'm the Child : %d\n",getpid());
	else
	{
		signal(SIGCHLD,function);
		printf("I'm the Parent : %d\n",getppid());
		while(1);
	}
	return 0;
}		
