//soe
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sched.h>
#include<math.h>
#include<string.h>
#include<stdbool.h>
int k=0;
int n=100,limit;
int prime[11];

void simpleSieve(int limit, int prime[])
{
int i,p;
    bool mark[limit+1];
    memset(mark, true, sizeof(mark));
 
    for (p=2; p*p<limit; p++)
    {
        if (mark[p] == true)
        {
            for (i=p*2; i<limit; i+=p)
                mark[i] = false;
        }
    }
    for ( p=2; p<limit; p++)
    {
        if (mark[p] == true)
        {
        prime[k++]=p;
        printf("%d ",p);
        }
    }
}
void *seg1(void *vargp){

int seive[35]={0},i,j;
for(i=0;i<k;i++)
{

j=(11/prime[i])*prime[i];
if(j<11)
j+=prime[i];
for(;j<=40;j+=prime[i])
{
if(j%prime[i]==0)
seive[j-11]=1;
}
}

for(i=11;i<=40;i++)
{
if(seive[i-11]==0)
printf("%d ",i);
}
}
void *seg2(void *vargp){

int seive[35]={0},i,j;
for(i=0;i<k;i++)
{

j=(41/prime[i])*prime[i];
if(j<41)
j+=prime[i];
for(;j<=70;j+=prime[i])
{
if(j%prime[i]==0)
seive[j-41]=1;
}
}

for(i=41;i<=70;i++)
{
if(seive[i-41]==0)
printf("%d ",i);
}
}
void *seg3(void *vargp){

int seive[35]={0},i,j;
for(i=0;i<k;i++)
{

j=(71/prime[i])*prime[i];
if(j<71)
j+=prime[i];
for(;j<=100;j+=prime[i])
{
if(j%prime[i]==0)
seive[j-71]=1;
}
}

for(i=71;i<=100;i++)
{
if(seive[i-71]==0)
printf("%d ",i);
}
}
int main(){
limit=10+1;
simpleSieve(limit,prime);
pthread_t tid1, tid2, tid3, tid4, tid5;
pthread_create(&tid3, NULL,seg3 , NULL);
pthread_create(&tid1, NULL,seg1 , NULL);
pthread_create(&tid2, NULL,seg2 , NULL);
pthread_join(tid3,NULL);
pthread_join(tid1,NULL);
pthread_join(tid2,NULL);
}
