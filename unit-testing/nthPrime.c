#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>

unsigned long long nthPrime(unsigned long long n);
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



unsigned long long nthPrime(unsigned long long n)
{
	unsigned long long prime, index, primes;

	primes = 2;
	index =  5;
	prime = 2;
/* using the 6k +- 1 optimization: all primes greater than 6 are of the form 6k +- 1. This is because all integers can be expressed as (6k+i) for some integer k and for i = -1, 0, 1, 2, 3 or 4; 2 divides (6k + 0), (6k + 2) and (6k + 4) and 3 divides (6k + 3). */
	
	if( n <= 0)
		return 0;
	if(n == 1)
		return prime;
	else if( n == 2 )
		return ++prime;
	else
		while(primes < n)
		{
			if( isPrime(index) )
			{
				primes++;
				prime = index;
			}

			if( isPrime(index+2) )
			{
				if(primes < n)
					prime = index+2;
				primes++;
			}

			index+=6;
		}
	return prime;
}

//Tells wheter the given number is prime.
bool isPrime(unsigned long long n)
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
