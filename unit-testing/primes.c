#include "primes.h"

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

//Tells you how many prime numbers are before the given number (inclusive).
unsigned long long piFunction(unsigned long long n)
{
	unsigned long long prime, index = 0;
	unsigned long long divisor;
	divisor = 5;
	index =  5
/* using the 6k +- 1 optimization: all primes greater than 6 are of the form 6k +- 1. This is because all integers can be expressed as (6k+i) for some integer k and for i = -1, 0, 1, 2, 3 or 4; 2 divides (6k + 0), (6k + 2) and (6k + 4) and 3 divides (6k + 3). */
	
	if(n < 2)
		return 0;
	else if( n <= 3 )
		return 2;
	else
		while(index <= n)
		{
/* we need only integer divisors less than or equal sqroot(n). Factors greater than that will result in a number always lower than n or always greater. */
			if( isPrime(index) );
				primes++;
			if( isPrime(index+2) )
				primes++;
			index+=6;
		}
	return index;
}

//Returns the nth prime, being -n-th the given number.
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

/*Prints or saves on a file all the possible prime numbers in the given time. If the name passed is a valid file name it will save them there, otherwise it will print them. It will print them on either stream (file/stdout) in a csv format with record size indicated by the blocks arg. */
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

/*Prints or saves on a file the first n prime numbers, where n is the passed number. If the name passed is a valid file name it will save them there, otherwise it will print them. It will print them on either stream (file/stdout) in a csv format with record size indicated by the blocks arg.*/

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

/*Saves on a pointer the first prime numbers that fit in X MB, where X is the passed number.*/
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


void listAllPrimes(char *fileName)
{
	unsigned long long n, divisor, primesToLoad;
	char primeBuff[200];
	bool isPrime1, isPrime2;
	FILE *primesFileR;
	
	n = 0;
	primesFileR = fopen(fileName, "r");// first tries to open the passed file and looks for the last prime found 
	if( primesFileR )
	{
		
		while( fscanf(primesFileR, "%s", primeBuff) != EOF )
			n = strtoull(primeBuff, NULL, 10);
		
		fflush(primesFileR);
		fclose(primesFileR);
	}

	
	if(n < 11) // if nothing was found (or only the base-primes were found), then overwrite the file and create a baseline.
	{
		primesFileR = fopen(fileName, "w");
		
		fprintf(primesFileR, "%u\n", 2);
		fprintf(primesFileR, "%u\n", 3);
		fprintf(primesFileR, "%u\n", 5);
		fprintf(primesFileR, "%u\n", 7);
		fclose(primesFileR);
		n = 11;
	}
	
	isPrime1 = true;
	isPrime2 = true;

	primesFileR = fopen(fileName,  "a+");// opens file for appending and reading 
	
	while(n < ULLONG_MAX && !STOP) // STOP will keep track of SIGINT (ctrl + c)
	{
/* using the 6k +- 1 optimization: all integers greater than 6 are of the form 6k +- 1. This is because all integers can be expressed as (6k+i) for some integer k and for i = -1, 0, 1, 2, 3 or 4; 2 divides (6k + 0), (6k + 2) and (6k + 4) and 3 divides (6k + 3). */
		primesToLoad = (unsigned long long)sqrt(n+2) + 1; // saving the square root of n+2 and adding 1 we don't miss the prime right before 
		
		divisor = 0;
		while( (divisor <= primesToLoad) && (isPrime1 || isPrime2) )//only testing the primes < sqrt(n+2) and we stop if both are composite.
		{
			fscanf(primesFileR, "%s", primeBuff);
			divisor = strtoull(primeBuff, NULL, 10);
			
			if( n%divisor == 0 )
				isPrime1 = false;
			if( (n+2)%divisor == 0 )
				isPrime2 = false;
		}

		//if they are prime, then write it in the file.
		if(isPrime1)
			fprintf(primesFileR, "%llu\n", n);
		if(isPrime2)
			fprintf(primesFileR, "%llu\n", (n+2) );
		
		n+=6;//step, because of the form 6k +- 1
		
		rewind(primesFileR);// rewind the cursor at the beginning and set the isPrime flags to true
		isPrime1 = true;
		isPrime2 = true;
	}

	fclose(primesFileR);// closing the file before exiting.
}

//Tells wheter the given number is prime WITHOUT any given list of primes.
bool isPrime_WList(unsigned long long int n, char *fileName)
{
	unsigned long long divisor, primesToLoad;
	char primeBuff[200];
	FILE *primesFileR;

	divisor = 5; 
/* using the 6k +- 1 optimization: all primes greater than 6 are of the form 6k +- 1. This is because all integers can be expressed as (6k+i) for some integer k and for i = -1, 0, 1, 2, 3 or 4; 2 divides (6k + 0), (6k + 2) and (6k + 4) and 3 divides (6k + 3). */
	if( n <= 3 ||  n == 5 || n == 7 )
		return true;
	else if( n%2 == 0 || n%3 == 0 || n%5 == 0 || n%7 == 0)// is not prime if can be divided by 2 or 3
		return false;
	else
	{
		primesToLoad = (unsigned long long)sqrt(n) + 1; // saving the sqrt of n and adding 1 we don't miss the prime right before 
		
		primesFileR = fopen(fileName, "r");
		
		fscanf(primesFileR, "%s", primeBuff);
		divisor = strtoull(primeBuff, NULL, 10);
		
		while( (divisor <= primesToLoad) )//only testing the primes < sqrt(n+2) and we stop if both are composite.
		{
			fscanf(primesFileR, "%s", primeBuff);
			divisor = strtoull(primeBuff, NULL, 10);
			
			if( n%divisor == 0 )
				return false;
		}
		fclose(primesFileR);
	}
	return true;
}


