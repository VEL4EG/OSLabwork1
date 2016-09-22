#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void inline printForkTime(clock_t before, clock_t after);

int main()
{
	clock_t secBeforeFork, secAfterFork;
	float a[1000000];

	secBeforeFork = clock();
	
	if (fork() > 0)
	{
		secAfterFork = clock();
	
		printf("If Child don't use big varible ");
		printForkTime(secBeforeFork, secAfterFork);
		
		secBeforeFork = clock();

		if( fork() > 0)
		{
			secAfterFork = clock();
			
			printf("If Child use big varible ");
			printForkTime(secBeforeFork, secAfterFork);
		}
		else
		a[31] = 1234;

	}

	return 0;
}

void printForkTime(clock_t before, clock_t after)
{
	if ((before == -1) || (after == -1))
	printf("Can't count fork time\n");
	else
	printf("fork time: %f seconds\n", 
				(float)(after - before) / CLOCKS_PER_SEC);
}
