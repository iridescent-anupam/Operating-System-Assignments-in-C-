#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>

int main(int argc,char *argv[])
{
    long long i;
    int *a = (int *) malloc(sizeof(int));
    
    for(i=1;i<=100;i++)
    {
       printf("%s address - %d \t Parent Process ID - %d \t Process ID - %d \t \n",argv[1],&a,getppid(),getpid());
    } 
    
    return 0;
}

