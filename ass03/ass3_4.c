//Killing a Zombie Process by ignoring the SIGCHLD signal 

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/wait.h> 
#include<sys/types.h> 

int main()
{
	if(!fork())
	{
		printf("I'm the Child : %d\n",getpid());
	}
	else
	{
		signal(SIGCHLD,SIG_IGN);
		printf("I'm the Parent :%d\n",getppid());
		while(1);
	}
	return 0;
}			
