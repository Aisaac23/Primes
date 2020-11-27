#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <signal.h>
#include "primes.h"

void signal_int_handler(int op);
volatile bool STOP;

int main(int argc, char* argv[])
{
	clock_t begin, end;
	begin = clock();
	float elapsed;
	
	printf("Limit:%llu\n", ULLONG_MAX);
	STOP = false;
	
	signal(SIGINT, &signal_int_handler);
	
	listAllPrimes(argv[1], strtoull(argv[2], NULL, 10));

	end = clock();

	elapsed = ((float)end - (float)begin) / (float)(CLOCKS_PER_SEC*60);
	printf("\nElapsed time: %.10f\n", elapsed );

	return EXIT_SUCCESS;
}

void signal_int_handler(int op)
{
	STOP = true;
}

