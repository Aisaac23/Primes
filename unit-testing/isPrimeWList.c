#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

bool isPrime_WList(unsigned long long n, unsigned long long *primeList, unsigned long long listLimit);
unsigned long long* loadPrimes(char *fileName, unsigned long long n);

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

	primeList = loadPrimes(argv[1], limit);

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

unsigned long long* loadPrimes(char *fileName, unsigned long long memLimit)
{

	unsigned long long *primeList, divisor, *first_ptr;
	const unsigned int DEC_DIGITS = 21;// 2^64 is 20 digits long.
	char primeBuff[DEC_DIGITS];
  
	FILE *primesFileR;

	primesFileR = fopen(fileName, "r");//opening the file for reading 

	primeList = malloc( memLimit*sizeof(unsigned long long) );
	first_ptr = primeList; // we save the first pointer to the allocated memory (valid pointer).
	
	while( memLimit > 0 )//getting a prime number from the list and saving it in corresponding pointer position.
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

//Tells wheter the given number is prime USING a precomputed list of primes.
bool isPrime_WList(unsigned long long n, unsigned long long *primeList, unsigned long long listLimit)
{
	unsigned long long divisor, primesToLoad;

	divisor = 5; 
/* using the 6k +- 1 optimization: all primes greater than 6 are of the form 6k +- 1. This is because all integers can be expressed as (6k+i) for some integer k and for i = -1, 0, 1, 2, 3 or 4; 2 divides (6k + 0), (6k + 2) and (6k + 4) and 3 divides (6k + 3). */
	if(n < 2)
		return false;
	else if( n <= 3 ||  n == 5 || n == 7 )
		return true;
	else if( n%2 == 0 || n%3 == 0 || n%5 == 0 || n%7 == 0)// is not prime if can be divided by 2, 3, 5 or 7
		return false;
	else
	{

		primesToLoad = primeList[listLimit-1]; // getting the last prime on the list 

		divisor = *(primeList+4);// we skip the four first primes since we already tested them: 2, 3, 5 and 7
		while( (divisor < primesToLoad) )
		{
			divisor = *(primeList++);
			if( n%divisor == 0 )
				return false;
		}

		while(divisor*divisor <= n)// if the list was not enough we use the regular (fast) method.
			if( n%divisor == 0 || n%(divisor+2) == 0 ) // testing 6k-1 (n%divisor) and 6k+1 (n%(divisors+2))
				return false;
			else
				divisor+=6;
	}
	return true;
}


