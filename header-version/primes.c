#include "primes.h"

bool isPrime(unsigned long long int n)
{
	unsigned long long divisor;
	divisor = 5; 
/* using the 6k +- 1 optimization: all primes greater than 6 are of the form 6k +- 1. This is because all integers can be expressed as (6k+i) for some integer k and for i = -1, 0, 1, 2, 3 or 4; 2 divides (6k + 0), (6k + 2) and (6k + 4) and 3 divides (6k + 3). */
	if( n <= 3 )
		return true;
	else if( n%2 == 0 || n%3 == 0)// is not prime if can be divided by 2 or 3
		return false;
	else
		while(divisor*divisor <= n)
		{
/* we need only integer divisors less than or equal sqroot(n). Factors greater than that will result in a number always lower than n or always greater. */
			if(n%divisor == 0 || n%(divisor+2) == 0 ) // if it can be divided by divisor or if divisor is even 
				return false;
			else
				divisor+=6;
		}
	return true;
}

unsigned long long piFunction(unsigned long long n)
{
	unsigned long long prime = 1, index = 0;
	while(prime < n)
	{
		prime++;
		if( isPrime(prime) )
			index++;
	}
	return index;
}

unsigned long long nthPrime(unsigned long long n)
{
	unsigned long long prime = 1, index = 1;
	while(index <= n)
	{
		prime++;
		if( isPrime(prime) )
			index++;
	}
	return prime;
}

void primesInTime(unsigned int timeInSeconds, char *fileName, unsigned int block)
{
	unsigned long long n = 2, index = 1;

	clock_t timeUp, tCounter;
	FILE *stream;


	if(fileName != NULL)
		stream = fopen(fileName, "a");
	else
		stream = stdout;
	if(stream == NULL)
		return;	

	tCounter = clock();
	timeUp = clock() + ( CLOCKS_PER_SEC*timeInSeconds );
	
	while(tCounter < timeUp)
	{
		
		if( isPrime(n) )
		{
			fprintf(stream, "%llu,", n);
			if(block !=-1 && index%block == 0)
				fprintf(stream, "\n");
			index++;
		}
		n++;		
		tCounter = clock();		
	}
}

void firstNPrimes(unsigned long long n, char *fileName, unsigned int block)
{
	unsigned long long prime = 1, index = 1;
	FILE *stream;
	
	if(fileName != NULL)
		stream = fopen(fileName, "a");
	else
		stream = stdout;
	if(stream == NULL)
		return;	

	while(index <= n)
	{
		prime++;
		if( isPrime(prime) )
		{
			fprintf(stream, "%llu,", prime);
			if(block !=-1 && index%block == 0)
				fprintf(stream, "\n");
			index++;
		}
	}

	return;
}

unsigned long long *primesInMemory(unsigned long long megaBytes)
{
	unsigned long long *primes, nPrimes, index = 1, prime = 1;
	const unsigned int ONE_MILLION = 1024*1024;
	
	nPrimes = (megaBytes*ONE_MILLION)/sizeof(unsigned long long);
	primes = calloc( nPrimes, sizeof(unsigned long long) );

	while(index < nPrimes)
	{
		prime++;
		if( isPrime(prime) )
		{
			primes[index] = prime;
			index++;
		}
	}
	primes[0] = nPrimes;
	
	return primes;
}


