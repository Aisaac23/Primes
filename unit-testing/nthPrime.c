#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include "primes.h"


bool isPrime(unsigned long long int n);

int main(int argc, char* argv[])
{
	clock_t begin, end;
	unsigned long long n, nth_Prime;
	float elapsed;

	n = strtoull(argv[1], NULL, 10);
	begin = clock();

	nth_Prime = nthPrime(n);

	end = clock();
	elapsed = ((float)end - (float)begin) / (float)(CLOCKS_PER_SEC);

	printf("%llu_Prime: %llu\n", n, nth_Prime);

	printf("Elapsed time: %f\n\n", elapsed);
	return EXIT_SUCCESS;
}

