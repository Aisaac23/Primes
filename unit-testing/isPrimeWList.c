#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <math.h>


bool isPrime_WList(unsigned long long n, unsigned long long *primeList, unsigned long long listLimit);
unsigned long long* loadPrimes(char *fileName, unsigned long long n);

int main(int argc, char* argv[])
{
	clock_t begin, end;
	bool isPrimeFlag;
	float elapsed;
	unsigned long long *primeList, n, limit;
	
	n = strtoull(argv[1], NULL, 10);
	limit = 1024/8;
	limit *=1024;
	limit *=2048;
	primeList = loadPrimes(argv[2], limit);

	printf("Limit:%llu\n", ULLONG_MAX);
	begin = clock();
	
	isPrimeFlag = isPrime_WList( n, primeList, limit );

	end = clock();

	if(isPrimeFlag)
		printf("true\n");
	else
		printf("false\n");

	elapsed = ((float)end - (float)begin) / (float)(CLOCKS_PER_SEC);

	printf("\nElapsed time: %.10f\n", elapsed );

	return EXIT_SUCCESS;
}

unsigned long long* loadPrimes(char *fileName, unsigned long long n)
{

	unsigned long long *primeList, primesToLoad, divisor, *first_ptr;
	char primeBuff[200];

	primesToLoad = n;  
	FILE *primesFileR;

	primesFileR = fopen(fileName, "r");

	primeList = malloc( primesToLoad*sizeof(unsigned long long) );
	first_ptr = primeList;
	
	fscanf(primesFileR, "%s", primeBuff);
	divisor = strtoull(primeBuff, NULL, 10);
	
	while( primesToLoad > 0 )//only testing the primes < sqrt(n+2) and we stop if both are composite.
	{
		fscanf(primesFileR, "%s", primeBuff);
		divisor = strtoull(primeBuff, NULL, 10);
		*(primeList++) = divisor;

		primesToLoad--;
	}

	fclose(primesFileR);
	printf("max:%llu\n", *(--primeList) );
	return first_ptr;
}

//Tells wheter the given number is prime WITHOUT any given list of primes.
bool isPrime_WList(unsigned long long n, unsigned long long *primeList, unsigned long long listLimit)
{
	unsigned long long divisor, primesToLoad;

	divisor = 5; 
/* using the 6k +- 1 optimization: all primes greater than 6 are of the form 6k +- 1. This is because all integers can be expressed as (6k+i) for some integer k and for i = -1, 0, 1, 2, 3 or 4; 2 divides (6k + 0), (6k + 2) and (6k + 4) and 3 divides (6k + 3). */
	if( n <= 3 ||  n == 5 || n == 7 )
		return true;
	else if( n%2 == 0 || n%3 == 0 || n%5 == 0 || n%7 == 0)// is not prime if can be divided by 2 or 3
		return false;
	else
	{

		primesToLoad = primeList[listLimit-1]; // saving the sqrt of n and adding 1 we don't miss the prime right before 

		divisor = *(primeList+4);
		while( (divisor < primesToLoad) )//only testing the primes < sqrt(n+2) and we stop if both are composite.
		{
			divisor = *(primeList++);
			
			if( n%divisor == 0 )
				return false;
		}

		while(divisor*divisor <= n)
		{
/* we need only integer divisors less than or equal sqroot(n). Factors greater than that will result in a number always lower than n or always greater. */
			if( n%divisor == 0 || n%(divisor+2) == 0 ) // if it can be divided by divisor or if divisor is even 
				return false;
			else
				divisor+=6;
		}
	}
	return true;
}


