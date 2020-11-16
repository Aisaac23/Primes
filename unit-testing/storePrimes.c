#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <signal.h>


void listAllPrimes(char *fileName);
void signal_int_handler(int op);

volatile bool STOP;

int main(int argc, char* argv[])
{
	clock_t begin, end;
	begin = clock();
	float elapsed;

	printf("Limit:%llu\n", ULLONG_MAX);
	STOP = false;
	
	signal(SIGINT, &signal_int_handler);
	
	listAllPrimes(argv[1]);

	end = clock();

	elapsed = ((float)end - (float)begin) / (float)(CLOCKS_PER_SEC*60);
	printf("\nElapsed time: %.10f\n", elapsed );

	return EXIT_SUCCESS;
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

void signal_int_handler(int op)
{
	STOP = true;
}
