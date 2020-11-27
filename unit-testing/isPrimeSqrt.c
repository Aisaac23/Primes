#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include "primes.h"

int main(int argc, char* argv[])
{
	clock_t begin, end;
	bool isPrimeFlag;
	float elapsed;

	begin = clock();

	printf("Limit:%llu\n", ULLONG_MAX); //max number that could be calculated 
	
	isPrimeFlag = isPrimeSqrt( strtoull(argv[1], NULL, 10) );

	end = clock();
	elapsed = ((float)end - (float)begin) / (float)(CLOCKS_PER_SEC);

	if(isPrimeFlag)
		printf("%s is prime.(sqrt)\n", argv[1]);
	else
		printf("%s is NOT prime.(sqrt)\n", argv[1]);

	printf("Elapsed time: %.10f\n\n", elapsed );

	return EXIT_SUCCESS;
}

