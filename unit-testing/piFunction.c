#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include "primes.h"

int main(int argc, char* argv[])
{
	clock_t begin, end;
	unsigned long long n, n_found;
	float elapsed;

	printf("Limit:%llu\n", ULLONG_MAX);
	n = strtoull(argv[1], NULL, 10);

	begin = clock();

	n_found = piFunction(n);

	end = clock();

	elapsed = ((float)end - (float)begin) / (float)(CLOCKS_PER_SEC);
	printf("Found %llu primes before %llu inclusive.\n", n_found, n);
	printf("Elapsed time: %f\n\n", elapsed );
	return EXIT_SUCCESS;
}

