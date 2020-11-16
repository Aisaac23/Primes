#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <float.h>


bool isPrime(unsigned long long int n);

int main(int argc, char* argv[])
{
	clock_t begin, end;
	bool isPrimeFlag;
	float elapsed;

	begin = clock();

	printf("Limit:%llu\n", ULLONG_MAX); //max number that could be calculated 
	
	isPrimeFlag = isPrime( strtoull(argv[1], NULL, 10) );

	end = clock();
	elapsed = ((float)end - (float)begin) / (float)(CLOCKS_PER_SEC);

	if(isPrimeFlag)
		printf("%s is prime.\n", argv[1]);
	else
		printf("%s is NOT prime.\n", argv[1]);

	printf("Elapsed time: %.10f\n\n", elapsed );

	return EXIT_SUCCESS;
}

//Tells wheter the given number is prime WITHOUT any given list of primes.
bool isPrime(unsigned long long int n)
{
	unsigned long long divisor;
	divisor = 5; 
/* using the 6k +- 1 optimization: all primes greater than 6 are of the form 6k +- 1. This is because all integers can be expressed as (6k+i) for some integer k and for i = -1, 0, 1, 2, 3 or 4; 2 divides (6k + 0), (6k + 2) and (6k + 4) and 3 divides (6k + 3). */
	if( n <= 3 && n >1)
		return true;
	else if( n%2 == 0 || n%3 == 0 || n == 1)// is not prime if can be divided by 2 or 3 or is 1
		return false;
	else
		while(divisor*divisor <= n)
		{
/* we need only integer divisors less than or equal sqroot(n). Factors greater than that will result in a number always lower than n or always greater. */
			if( n%divisor == 0 || n%(divisor+2) == 0 ) // if it can be divided by divisor or if divisor is even 
				return false;
			else
				divisor+=6;
		}
	return true;
}

