//Program which creates 4 threads T1, T2, T3 and T4. Each thread Ti should add i repeatedly to a shared globalvariable x. All threads should run until exceeds an upper limit M. (done by Bakery Algorithm)
#define _GNU_SOURCE
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdbool.h>

int x=0,M=100;
bool flag[4];
int num[4]={0};
int turn=0;
int cnt1=0,cnt2=0,cnt3=0,cnt4=0;

int max(int a,int b)
{
	if(a>b)
		return a;
	else
		return b;
}

int comp(int a,int b,int c,int d)
{
	if(a<c||(a==c)&&b<d)
		return 1;
	else
		return 2;
}


void *sum1(void *vargp)
{
	while(1)
	{
		if(x>M)
			pthread_exit(0);
			
		flag[0]=true;
		num[0]=max(max(num[0],num[1]),max(num[2],num[3]))+1;
		flag[0]=false;
		for(j=0;j<4;j++)
		{
			while(flag[j]);
			while((num[j]!=0)&&(comp(num[j],j,num[0],0))==1);
		}
		x+=1;
		cnt1++;
		if(x==(cnt1+2*cnt2+3*cnt3+4*cnt4))
        		printf("x=%d,cnt1=%d,cnt2=%d,cnt3=%d,cnt4=%d\n",x,cnt1,cnt2,cnt3,cnt4);
        	else
        		printf("Error\n");
    		num[0]=0;
	}
}

void *sum2(void *vargp)
{
	while(1)
	{
		if(x>M)
			pthread_exit(0);

		flag[1]=true;
		num[1]=max(max(num[0],num[1]),max(num[2],num[3]))+1;
		flag[1]=false;
		for(j=0;j<4;j++)
		{
			while(flag[j]);
			while((num[j]!=0)&&(comp(num[j],j,num[1],1))==1);
		}
		x+=2;
		cnt2++;
		if(x==(cnt1+2*cnt2+3*cnt3+4*cnt4))
        		printf("x=%d,cnt1=%d,cnt2=%d,cnt3=%d,cnt4=%d\n",x,cnt1,cnt2,cnt3,cnt4);
        	else
        		printf("Error\n");
    		num[1]=0;
	}
}


void *sum3(void *vargp)
{
	while(1)
	{
		if(x>M)
		pthread_exit(0);

		flag[2]=true;
		num[2]=max(max(num[0],num[1]),max(num[2],num[3]))+1;
		flag[2]=false;
		for(j=0;j<4;j++)
		{
			while(flag[j]);
			while((num[j]!=0)&&(comp(num[j],j,num[2],2))==1);
		}
		x+=3;
		cnt3++;
		if(x==(cnt1+2*cnt2+3*cnt3+4*cnt4))
        		printf("x=%d,cnt1=%d,cnt2=%d,cnt3=%d,cnt4=%d\n",x,cnt1,cnt2,cnt3,cnt4);
        	else
        		printf("Error\n");
    		num[2]=0;
	}
}


void *sum4(void *vargp)
{
	while(1)
	{
		if(x>M)
		pthread_exit(0);

		flag[3]=true;
		num[3]=max(max(num[0],num[1]),max(num[2],num[3]))+1;
		flag[3]=false;
		for(j=0;j<4;j++)
		{
			while(flag[j]);
			while((num[j]!=0)&&(comp(num[j],j,num[3],3))==1);
		}
		x+=4;
		cnt4++;
		if(x==(cnt1+2*cnt2+3*cnt3+4*cnt4))
        		printf("x=%d,cnt1=%d,cnt2=%d,cnt3=%d,cnt4=%d\n",x,cnt1,cnt2,cnt3,cnt4);
        	else
        		printf("Error\n");
    		num[3]=0;
	}
}


int main()
{
	int i=10;
	pthread_t add1,add2,add3,add4;
	flag[0]=flag[1]=flag[2]=flag[3]=true;
	pthread_create(&add1,NULL,sum1,NULL);
	pthread_create(&add2,NULL,sum2,NULL);
	pthread_create(&add4,NULL,sum4,NULL);
	pthread_create(&add3,NULL,sum3,NULL);
	pthread_join(add1,NULL);
	pthread_join(add2,NULL);
	pthread_join(add3,NULL);
	pthread_join(add4,NULL);
	return 0;
}
