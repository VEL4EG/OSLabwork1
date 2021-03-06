#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#define ELEM_COUNT 1000000

typedef struct timeval timeval;

void inline getTime(timeval *t); 
void inline printForkTime(timeval *before, timeval *after); 

int main() 
{ 
	timeval beforeFork, afterFork; 
	float a[ELEM_COUNT];

	for (int i = 0; i < ELEM_COUNT; i++)
	a[i] = i;
	
	getTime(&beforeFork); 
	
	if (fork() > 0)
	{
		getTime(&afterFork);
	
		printf("If Child don't use big varible, Parent fork time: ");
		printForkTime(&beforeFork, &afterFork);
		
		getTime(&beforeFork);

		if( fork() > 0)
		{		
			getTime(&afterFork);
			
			printf("If Child use big varible, Parent fork time: ");
			printForkTime(&beforeFork, &afterFork);
		}
		else
		{
			a[31] = 1234;

			getTime(&afterFork);
		
			printf("If Child use big varible, Child fork time: ");
			printForkTime(&beforeFork, &afterFork);
		}

	}
	else
	{
		getTime(&afterFork);
	
		printf("If Child don't use big varible, Child fork time: ");
		printForkTime(&beforeFork, &afterFork);
	}
	return 0;
}

void getTime(timeval *t)
{
	static struct timezone tz;

	if (gettimeofday(t, &tz) == -1)
	{
		printf("Can't get time\n");
		exit(EXIT_FAILURE);
	}
}

void printForkTime(timeval *before, timeval *after)
{

	printf("%ld microseconds\n", (after->tv_sec - before->tv_sec)/1000000 + 
								 after->tv_usec - before->tv_usec);
}
