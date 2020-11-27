#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include "primes.h"

int main(int argc, char* argv[])
{
	unsigned long long *list, memLimit, memLimit_aux;
	unsigned long SIZE_ULL = sizeof(unsigned long long);
	float elapsed;
	clock_t begin, end;

	memLimit = strtoull(argv[2], NULL, 10);
	memLimit_aux = memLimit;
	memLimit /= SIZE_ULL;
	

	begin = clock();
	list = loadPrimes(argv[1], &memLimit);
	end = clock();
	
	printf("Last prime stored: %llu using %llu bytes.\n", list[memLimit-1], memLimit_aux);
	printf("llu blocks of memory available %llu, of size: %lu\n", memLimit, SIZE_ULL);

	elapsed = ((float)end - (float)begin) / (float)(CLOCKS_PER_SEC);
	printf("Elapsed time: %.10f\n", elapsed );

	printf("Press any key to continue...");
	getchar();
	printf("\n");

	return EXIT_SUCCESS;
}

