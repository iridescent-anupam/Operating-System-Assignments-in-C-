//Killing a Zombie Process by using a Grandchild process

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int pid;
	pid = fork();
	
	if (pid==0)
	{
		pid=fork();
		if (pid==0)
			printf("I'm the Grandchild : %d\nI'm the Child : %d\n",getpid(),getppid());
	}
	else
	{
		wait(NULL);
		sleep(10);
	}	
	return 0;
}		
