/*This program could take as argument the following:

-t [time_in_seconds]-> Generates all the possible prime numbers in the given time.
-p [any_positive_integer] -> Tells you how many prime numbers are before the given number (inclusive).
-n [any_positive_integer] -> Returns the nth prime, being -n-th the given number.
-i [any_positive_integer] -> Tells wheter the given number is prime.
-f [any_positive_integer] -> Prints or saves on a file the first n prime numbers, where n is the passed number.
-m [any_positive_integer] -> Saves on a pointer the first prime numbers that fit in X MB, where X is the passed number.

*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>
#include "chkops.h"


void firstNPrimes(unsigned long long n);
unsigned long long nthPrime(unsigned long long top);
bool isPrime(unsigned long long int n);
unsigned long long piFunction(unsigned long long n);
void primesInTime(unsigned int timeInSeconds);
unsigned long long *primesInMemory(unsigned long long megaBytes);

void pause(void);
int inBlocks(const char* output);
bool askIfSave(void);
int menu(char* argv[]);
char *setFileName(void);

char *fileName;

int main(int argc, char* argv[])
{
	char fn[11] = "primes.txt";
	fileName = fn;
	fileName = setFileName();

	if(menu(argv) == -1 || argc < 4)
	{
		printf("Arguments missing or with the wrong format in: %s\n", argv[0]);
		exit(EXIT_SUCCESS);
	}
	return EXIT_SUCCESS;
}

int menu(char *argv[])
{
	char opc[1];
	opc[0] = argv[1][1];
	if(argv[1][0] != '-')
		return -1;

	switch(opc[0])
	{
		case 't':
			if( isUnsignedInteger( argv[2] ) )
				primesInTime( atoi(argv[2]) );
		break;

		case 'p':
			if( isUnsignedInteger( argv[2] ) )
				printf("There are %llu primes lower or equal than %llu.\n", piFunction( atoi(argv[2]) ), (unsigned long long)atoi(argv[2]) );
		break;

		case 'n':
			if( isUnsignedInteger( argv[2] ) )
				printf("The %llu-nth prime is %llu.\n", (unsigned long long)atoi(argv[2]), nthPrime( atoi(argv[2]) ) );
		break;
		
		case 'i':
			if( isUnsignedInteger( argv[2] ) )
			{
				if( isPrime( atoi(argv[2] ) ) )
					printf("\nIt IS prime number.\n");
				else
					printf("\nIt's NOT prime number.\n");
			}
		break;

		case 'f':
			if( isUnsignedInteger( argv[2] ) )
				firstNPrimes( atoi(argv[2]) );
		break;

		case 'm':
			if( isUnsignedInteger( argv[2] ) )
				primesInMemory( atoi(argv[2]) );
		break;

	};
	return -1;
	
}

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

void primesInTime(unsigned int timeInSeconds)
{
	int block = -1;
	unsigned long long n = 2, index = 1;
	bool save;
	clock_t timeUp, tCounter;
	FILE *stream;

	save = askIfSave();
	stream = save ? fopen(fileName, "a") : stdout;
	
	block = save ? inBlocks("save") : inBlocks("display");
	
	tCounter = clock();
	timeUp = clock() + ( CLOCKS_PER_SEC*timeInSeconds );
	
	while(tCounter < timeUp)
	{
		
		if( isPrime(n) )
		{
			fprintf(stream, "%llu,", n);
			if(block !=-1 && index%block == 0)
			{
				if(save)
					fprintf(stream, "\n");
				else
					pause();
			}
			index++;
		}
		n++;		
		tCounter = clock();		
	}

	if(save)
	{
		printf("\n\nYour %llu prime numbers have been saved at %s.\n", index, fileName);
		fclose(stream);
	}
	else
		printf("\n\nA total of %llu prime numbers have been found.\n", index);
}

void firstNPrimes(unsigned long long n)
{
	unsigned long long prime = 1, index = 1;
	int block = -1;
	FILE *stream;
	bool save;
	
	save = askIfSave();
	stream = save ? fopen(fileName, "a") : stdout;

	block = save ? inBlocks("save") : inBlocks("display");
		
	while(index <= n)
	{
		prime++;
		if( isPrime(prime) )
		{
			fprintf(stream, "%llu,", prime);
			if(block !=-1 && index%block == 0)
			{
				if(save)
					fprintf(stream, "\n");
				else
					pause();
			}
			index++;
		}
	}
	if(save)
	{
		printf("\n\nYour %llu prime numbers have been saved at %s.\n", n, fileName);
		fclose(stream);
	}
	printf("\n");
	return;
}

unsigned long long *primesInMemory(unsigned long long megaBytes)
{
	unsigned long long *primes, nPrimes, index = 1, prime = 1;
	const unsigned int ONE_MILLION = 1024*1024;
	int block = -1;
	bool save;
	FILE *stream;

	save = askIfSave();
	stream = save ? fopen(fileName, "a") : stdout;
	
	block = save ? inBlocks("save") : inBlocks("display");
	
	nPrimes = (megaBytes*ONE_MILLION)/sizeof(unsigned long long);
	primes = calloc( nPrimes, sizeof(unsigned long long) );

	while(index < nPrimes)
	{
		prime++;
		if( isPrime(prime) )
		{
			primes[index] = prime;

			fprintf(stream, "%llu,", prime);
			if(block !=-1 && index%block == 0)
			{
				if(save)
					fprintf(stream, "\n");
				else
					pause();
			}
			index++;
		}
	}

	if(save)
	{
		printf("\n\nYour %llu prime numbers have been saved at %s.\n", index, fileName);
		fclose(stream);
	}
	else
		printf("\n\nA total of %llu prime numbers have been found.\n", index);
	
	pause();
	
	primes[0] = nPrimes;
	return primes;
}


bool askIfSave(void)
{
	char answer;
	printf("\nWould you wish to store them in disc? (y/n)\n");
	scanf(" %c", &answer);

	if( answer == 'y')
		return true;		
	else
		return false;	
}

int inBlocks(const char* output)
{
	char answer;
	printf("\nWould you wish to %s them in blocks? (y/n)\n", output);
	scanf(" %c", &answer);

	if( answer == 'y')
	{
		int size = 0;
		printf("Please provide the size of the block (0-300):");
		scanf(" %i", &size);
		return size;
	}
	else
		return -1;
}

char *setFileName(void)
{
	char answer, *newName;
	printf("\nThe current file's name is: %s", fileName);
	printf("\nWould you wish to change it? (y/n)\n");
	scanf(" %c", &answer);

	if( answer == 'y')
	{
		newName = calloc(256, sizeof(char));
		printf("Please provide the new file name: ");
		scanf(" %s", newName);
		return newName;
	}
	else
		return fileName;
}

void pause(void)
{
	getchar();
	printf("\nPress any key to continue...");
	getchar();
	printf("\n");	
}


