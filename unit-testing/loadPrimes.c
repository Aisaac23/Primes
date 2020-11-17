#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>


unsigned long long* loadPrimes(char *fileName, unsigned long long memLimit);

int main(int argc, char* argv[])
{
	unsigned long long *list, memLimit;
	unsigned long SIZE_ULL = sizeof(unsigned long long);
	float elapsed;
	clock_t begin, end;

	memLimit = strtoull(argv[2], NULL, 10);
	memLimit /= SIZE_ULL;

	begin = clock();
	list = loadPrimes(argv[1], memLimit);
	end = clock();

	printf("Last prime stored: %llu using %llu bytes.\n", list[memLimit-1], memLimit*SIZE_ULL);

	elapsed = ((float)end - (float)begin) / (float)(CLOCKS_PER_SEC);
	printf("\nElapsed time: %.10f\n", elapsed );

	printf("Press any key to continue...");
	getchar();

	return EXIT_SUCCESS;
}

unsigned long long* loadPrimes(char *fileName, unsigned long long memLimit)
{

	unsigned long long *primeList, divisor, *first_ptr;
	const unsigned int DEC_DIGITS = 21;
	char primeBuff[DEC_DIGITS];
  
	FILE *primesFileR;

	primesFileR = fopen(fileName, "r");

	primeList = malloc( memLimit*sizeof(unsigned long long) );
	first_ptr = primeList;
	
	while( memLimit > 0 )
	{
		fscanf(primesFileR, "%s", primeBuff);
		divisor = strtoull(primeBuff, NULL, 10);
		*primeList = divisor;
		primeList++;
		
		memLimit--;
	}

	fclose(primesFileR);
	return first_ptr;
}

