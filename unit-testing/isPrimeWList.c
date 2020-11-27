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
	unsigned long long *primeList, n, limit;
	const unsigned long long SIZE_ULL = sizeof(unsigned long long);
	const int TO_TEST = 12;
	char *primes[] = {"1844674407370955197","7919","8731","2844674407370955239", "3844674407370955331", 
	"4844674407370955273", "8844674407370955277", "10844674407370955251", "11844674407370955247", "15844674407370955303", 
	"17844674407370955271", "18446744003700551681"};
	

	limit = strtoull(argv[2], NULL, 10);
	limit /= SIZE_ULL;

	primeList = loadPrimes(argv[1], &limit);

	printf("Limit:%llu\n", ULLONG_MAX);
	
	for(int index = 0; index < TO_TEST; index++)
	{
		n = strtoull(primes[index], NULL, 10);
		begin = clock();
		
		isPrimeFlag = isPrime_WList( n, primeList, limit );

		end = clock();
		elapsed = ((float)end - (float)begin) / (float)(CLOCKS_PER_SEC);

		if(isPrimeFlag)
			printf("%s is prime.(Using list)\n", primes[index]);
		else
			printf("%s is NOT prime.(Using list)\n", primes[index]);

		printf("Elapsed time: %.10f\n\n", elapsed );
	}
	return EXIT_SUCCESS;
}

