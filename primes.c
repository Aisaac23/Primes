/*This program could take as argument the following:

-t [time_in_seconds] [space_in_memory_in_MB] -> generates all the possible prime numbers in the given time, without going over the given space in memory. If there's still time left but no space, then it gives you the option to save them in a file or display them and continue.

-p [any_positive_integer] -> Tells you how many prime numbers are before the given number (inclusive).
-n [any_positive_integer] -> Returns the nth prime, being -n-th the given number.
-i [any_positive_integer] -> Tells wheter the given number is prime.
*/

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

unsigned long long* primesInTime(unsigned int timeInSeconds, unsigned int memAvailable);
void delay(unsigned int seconds);
unsigned long long nthPrime(unsigned long long top);
bool isPrime(unsigned long long int n);
int askIfDisplay(void);
void displayPrimes(unsigned long long arraySize, unsigned long long *allPrimes, unsigned int blockSize);
bool askIfSave(void);
int savePrimesInDisk(unsigned long long arraySize, unsigned long long *allPrimes);
unsigned long long piFunction(unsigned long long n);
void menu(char* argv[]);

unsigned long long *primes;
int main(int argc, char* argv[])
{
	menu(argv);
	return 0;
}

void menu(char *argv[])
{
	char opc[1];
	opc[0] = argv[1][1];
	switch(opc[0])
	{
		case 't':
			primesInTime( atoi(argv[2]), atoi(argv[3]) );
		break;

		case 'p':
			printf("There are %llu primes lower or equal than %llu.\n", piFunction( atoi(argv[2]) ), (unsigned long long)atoi(argv[2]) );
		break;

		case 'n':
			printf("The %llu-nth prime is %llu.\n", (unsigned long long)atoi(argv[2]), nthPrime( atoi(argv[2]) ) );
		break;
		
		case 'i':
			if( isPrime( atoi(argv[2] ) ) )
				printf("\nIt IS prime number.\n");
			else
				printf("\nIt's NOT prime number.\n");
		break;

	};
	return;
	
}

void delay(unsigned int seconds)
{
	clock_t tOneScond, tCounter;
	tCounter = clock();
	tOneScond = clock()+CLOCKS_PER_SEC;
	while(tCounter < tOneScond)
		tCounter = clock();
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


unsigned long long* primesInTime(unsigned int timeInSeconds, unsigned int memAvailable)
{
	const unsigned int ONE_MILLION = 1024*1024;
	int blockSize;
	unsigned long long n = 2, nPrimes, index = 0, totalAmount = 0;
	clock_t timeUp, tCounter;

	nPrimes = memAvailable*ONE_MILLION/sizeof(unsigned long long);
	primes = calloc(memAvailable*ONE_MILLION/sizeof(unsigned long long), sizeof(unsigned long long) );
	
	tCounter = clock();
	timeUp = clock() + ( CLOCKS_PER_SEC*timeInSeconds );
	
	while(tCounter < timeUp)
	{
		
		if( isPrime(n) )
			primes[index++] = n;
		if(index == nPrimes)
		{
			totalAmount += index;
			printf("\n%llu new prime numbers have been found.\n", index);
			printf("\nThere's no more space available out of the %u MB that you provided in memory.\n", memAvailable);	
			if( askIfSave() )
			{
				savePrimesInDisk(index, primes);
				free(primes);
				primes = calloc(memAvailable*ONE_MILLION, sizeof(unsigned long long) );
				index = 0;
			}
			else if( (blockSize = askIfDisplay() ) != -1 )
			{
				displayPrimes( index, primes, blockSize );
				free(primes);
				primes = calloc(memAvailable*ONE_MILLION, sizeof(unsigned long long) );
				index = 0;
			}
		}
		n++;			
		tCounter = clock();		
	}
	totalAmount += index;
	if( askIfSave() )
	{
		if( savePrimesInDisk(index, primes) == 0)
			printf("\n\nYour %llu prime numbers have been saved.\n", index);
		free(primes);
	}
	else if( (blockSize = askIfDisplay() ) != -1 )
		displayPrimes( index, primes, blockSize );

	printf("\n\nA total of %llu prime numbers have been found.\n", totalAmount);
	
	return primes;
}

int savePrimesInDisk(unsigned long long arraySize, unsigned long long *allPrimes)
{
	FILE *primesInDisk;
	primesInDisk = fopen("primes.txt", "a");
	unsigned long long index = 0;
	while(index < arraySize)
	{
		fprintf(primesInDisk, "%llu,", allPrimes[index]);
		if(index%100 == 0 && index > 0)
			fprintf(primesInDisk, "\n");
		index++;
	}
	//return 0;
	return fclose(primesInDisk);
}

bool askIfSave(void)
{
	char answer;
	printf("\nWould you wish to store them in disc and continue? (y/n)\n");
	scanf(" %c", &answer);

	if( answer == 'y')
		return true;		
	else
		return false;	
}

int askIfDisplay(void)
{
	char answer;
	printf("\nWould you wish to display them in blocks? (y/n)\n");
	scanf(" %c", &answer);

	if( answer == 'y')
	{
		int size = 0;
		printf("Please provide the size of the block (0-300):");
		scanf("%i", &size);
		return size;
	}
	else
		return -1;
}

void displayPrimes(unsigned long long arraySize, unsigned long long *allPrimes, unsigned int blockSize)
{
	do
	{
		arraySize--;
		printf("%llu\n", allPrimes[arraySize]);

		if( arraySize%blockSize == 0 )
		{
			printf("\n\nPress any key to continue...\n");
			getchar();
		}
			
	}while(arraySize > 0);
	return;
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
