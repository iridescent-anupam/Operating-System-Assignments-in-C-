#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main(int argc,char *argv[])
{
	long i;
	int *a = (int *) malloc(sizeof(int));
	
	for(i=0;i<1000;i++)
	{
		printf("%s ---> Memory Address - %d\n",argv[1],&a);
	}
	return 0;
}		
