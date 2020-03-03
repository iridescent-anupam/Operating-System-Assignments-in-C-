// Implementing the Memory Mountain

#include<stdio.h>
#include<stdlib.h>
#include "clock.h"
#include "fcyc2.h"

#define MINBYTES (1 << 10)  //Working set size ranges from 1 KB
#define MAXBYTES (1 << 23)  //up to 8 MB
#define MAXSTRIDE 16        //Strides range from 1 to 16
#define MAXELEMS MAXBYTES/sizeof(int)

int data[MAXELEMS]; 	   //The array we'll be traversing


void test(int elems,int stride)   //The test function : Iterate over first "elems" elements of array "data"  with stride of "stride"
{
	int i;
	int result = 0;
	volatile int sink;
	for (i=0;i<elems;i+=stride)
	result += data[i];
	sink = result;    //So compiler doesn't optimize away the loop
}


double run(int size,int stride,double Mhz)   //Run test(elems,stride) and return read throughput (MB/s). "size" is in bytes, "stride" is in array elements, and Mhz is 							CPU clock frequency in Mhz.
{
	double cycles;
	int elems = size/sizeof(int);
	test(elems,stride);   			   //warm up the cache
	cycles = fcyc2(test, elems, stride, 0);    //call test(elems,stride)
	return (size / stride) / (cycles / Mhz);   //convert cycles to MB/s
}


int main()
{
	int size;      //Working set size (in bytes)
	int stride;    //Stride (in array elements)
	double Mhz;    //Clock frequency
	init_data(data, MAXELEMS);   //Initialize each element in data to 1
	Mhz = mhz(0);  //Estimate the clock frequency
	for(size = MAXBYTES; size >= MINBYTES; size >>= 1)
	{
		for (stride = 1; stride <= MAXSTRIDE; stride++)
		printf("%.1f\t", run(size, stride, Mhz));
		printf("\n");
	}
	exit(0);
}
