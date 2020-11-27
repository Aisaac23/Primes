#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include "primes.h"

int main(int argc, char* argv[])
{
	clock_t begin, end;
	bool isPrimeFlag;
	float elapsed;

	begin = clock();

	printf("Limit:%llu\n", ULLONG_MAX);
	
	isPrimeFlag = isPrime_L2( strtoull(argv[1], NULL, 10) );

	end = clock();
	elapsed = ((float)end - (float)begin) / (float)(CLOCKS_PER_SEC);

	if(isPrimeFlag)
		printf("%s is prime.(L2)\n", argv[1]);
	else
		printf("%s is NOT prime.(L2)\n", argv[1]);

	printf("Elapsed time: %.10f\n\n", elapsed );

	return EXIT_SUCCESS;
}

