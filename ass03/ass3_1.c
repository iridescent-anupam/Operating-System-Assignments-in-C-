//Creating a Zombie process

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	int p;
	p=fork();
	if(p>0)
	{
		printf("I'm the Parent : %d",getpid());
		while(1);
	}
	else
		exit(0);
	return 0;
}		
