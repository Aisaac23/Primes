#include "primes.h"

//Tells wheter the given number is prime.
bool isPrime(unsigned long long n)
{
	unsigned long long divisor;
	divisor = 5; 
/* using the 6k +- 1 optimization: all primes greater than 6 are of the form 6k +- 1. 
This is because all integers can be expressed as (6k+i) for some integer k and for i = -1, 0, 1, 2, 3 or 4; 
2 divides (6k + 0), (6k + 2) and (6k + 4) and 3 divides (6k + 3). */
	if( n < 2 )
		return false;
	else if( n < 4 )
		return true;
	else if( n%2 == 0 || n%3 == 0)// is not prime if can be divided by 2 or 3
		return false;
	else
		do
		{
/* we need only integer divisors less than or equal sqroot(n). 
Factors greater than that will result in a number always greater than n. */
			if( n%divisor == 0 || n%(divisor+2) == 0 ) // Here we test primes against n but also we need to test obvious numbers like 25
				return false;
			else
				divisor+=6;
		}while(divisor*divisor < n)

	return true;
}

bool isPrime_L1(unsigned long long int n)
{
	unsigned long long divisor;

	divisor = 5; 
	
	if( n < 2)
		return false;
	else if( n <= 3 )
		return true;
	else if( n%2 == 0 || n%3 == 0)// is not prime if can be divided by 2 or 3
		return false;
	else
		while(divisor <= n/2)// this is the simplest and slowest algorithm...
			if( n%divisor == 0 )//2 is the lowest divisor of any n, so any number greater than n/2 multiplied by any... 
				return false; // integer greater than 1 would result in a number greater than n.
			else
				divisor++;
	return true;
}

bool isPrime_L2(unsigned long long int n)
{
	unsigned long long divisor;
	divisor = 5;
 
	if( n < 2)
		return false;
	else if( n <= 3 )
		return true;
	else if( n%2 == 0 || n%3 == 0)// is not prime if can be divided by 2 or 3
		return false;
	else
		while(divisor*divisor <= n)// this is also a simple form but a litle faster. 
		{
			if( n%divisor == 0 )// sqrt(n) is the greatest factor of n where the two factors are the same. 
				return false; // we cannot find a factor greater than sqrt(n) because it'd yield a number greater than n.
			else
				divisor++; // additionally, being sqrt(n) = m, any divisor found in m is also a divisor in m for m*m = n.
		}
	return true;
}



//Tells wheter the given number is prime WITHOUT any given list of primes.
bool isPrimeSqrt(unsigned long long int n)
{
	unsigned long long divisor, sqroot;
	divisor = 5;
	sqroot = sqrt(n) + 1; 
/* using the 6k +- 1 optimization: all primes greater than 6 are of the form 6k +- 1. This is because all integers can be expressed as (6k+i) for some integer k and for i = -1, 0, 1, 2, 3 or 4; 2 divides (6k + 0), (6k + 2) and (6k + 4) and 3 divides (6k + 3). */
	if( n < 2 )
		return false;
	else if( n <= 3 )
		return true;
	else if( n%2 == 0 || n%3 == 0)// is not prime if can be divided by 2 or 3 or is 1
		return false;
	else
		while(divisor <= sqroot)/*Only integer divisors <= sqroot(n). Factors greater than that will result in a number always > n. */
			if( n%divisor == 0 || n%(divisor+2) == 0 ) // testing 6k-1 (n%divisor) and 6k+1 (n%(divisors+2))
				return false;
			else
				divisor+=6;
	return true;
}

unsigned long long* loadPrimes(char *fileName, unsigned long long *memLimit)
{

	unsigned long long *primeList, divisor, *first_ptr;
	const unsigned int DEC_DIGITS = 21;// 2^64 is 20 digits long.
	char primeBuff[DEC_DIGITS];
  
	FILE *primesFileR;

	primesFileR = fopen(fileName, "r");//opening the file for reading 

	primeList = malloc( (*memLimit)*sizeof(unsigned long long) );
	first_ptr = primeList; // we save the first pointer to the allocated memory (valid pointer).
	
	while( (*memLimit) > 0 && fscanf(primesFileR, "%s", primeBuff) != EOF)//getting primes from text file until memory limit or EOF.
	{
		divisor = strtoull(primeBuff, NULL, 10);
		*primeList = divisor;

		primeList++;
		(*memLimit)--;
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
		while( (divisor*divisor < primesToLoad) )
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

unsigned long long piFunction(unsigned long long n)
{
	unsigned long long primes, index;

	index =  5;
	primes = 2;
/* using the 6k +- 1 optimization: all primes greater than 6 are of the form 6k +- 1. This is because all integers can be expressed as (6k+i) for some integer k and for i = -1, 0, 1, 2, 3 or 4; 2 divides (6k + 0), (6k + 2) and (6k + 4) and 3 divides (6k + 3). */
	
	if(n < 2)
		return 0;
	else if( n == 2 )
		return 1;
	else if( n == 3 )
		return primes;
	else
		while(index <= n)
		{
			if( isPrime(index) )
				primes++;
			if( isPrime(index+2) && index+2 <= n )
				primes++;
			index+=6;
		}
	return primes;
}

void listAllPrimes(char *fileName, unsigned long long memLimit)
{
	unsigned long long n, primesToLoad, *primeList;
	unsigned int SIZE_ULL, BASE_PRIMES;
	bool isPrime1, isPrime2;
	FILE *primesFileR;
	
	n = 0;
	SIZE_ULL = sizeof(unsigned long long);
	BASE_PRIMES = 3;

	primesFileR = fopen(fileName, "r");// first tries to open the passed file and load all the primes that memLimit permits.
	
	if( primesFileR == NULL ) // if nothing was found (or only the base-primes were found), then overwrite the file and create a baseline.
	{
		primesFileR = fopen(fileName, "w+");
		
		fprintf(primesFileR, "%u\n", 2);
		fprintf(primesFileR, "%u\n", 3);
		fprintf(primesFileR, "%u\n", 5);

		memLimit = SIZE_ULL*BASE_PRIMES;
		fclose(primesFileR);
	}

	memLimit /= SIZE_ULL;
	primesToLoad = memLimit;
	primeList = loadPrimes(fileName, &memLimit);

	primesToLoad -= memLimit;
	n = primeList[ primesToLoad-1 ];// in case there was less primes in the file than what memLimit permits.
	
	primesFileR = fopen(fileName,  "a+");// opens file for appending and reading

	isPrime2 = isPrime_WList(n+2, primeList, primesToLoad);

	if(isPrime2)
	{
		fprintf(primesFileR, "%llu\n", n+2);
		primesToLoad++;
		primeList = realloc(primeList, primesToLoad*SIZE_ULL );
		primeList[primesToLoad-1] = n+2;
	}
	
	n+=6;//step, because of the form 6k +- 1

	while(n < ULLONG_MAX && !LIST_ALL_PRIMES_STOP) // LIST_ALL_PRIMES_STOP will keep track of SIGINT (ctrl + c)
	{
		isPrime1 = isPrime_WList(n, primeList, primesToLoad);;

		isPrime2 = isPrime_WList(n+2, primeList, primesToLoad);

		//if they are prime, then write it in the file.
		if(isPrime1)
		{
			fprintf(primesFileR, "%llu\n", n);
/*			primesToLoad++;*/
/*			primeList = realloc(primeList, primesToLoad*SIZE_ULL );*/
/*			primeList[primesToLoad-1] = n;*/
		}
		if(isPrime2)
		{
			fprintf(primesFileR, "%llu\n", n+2);
/*			primesToLoad++;*/
/*			primeList = realloc(primeList, primesToLoad*SIZE_ULL );*/
/*			primeList[primesToLoad-1] = n+2;*/
		}
		
		n+=6;//step, because of the form 6k +- 1
	}

	fclose(primesFileR);// closing the file before exiting.
}
