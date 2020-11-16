#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include <time.h>
#include <math.h>
#include <float.h>

bool isPrime_L1(unsigned long long int n);

int main(int argc, char* argv[])
{
	clock_t begin, end;
	bool isPrimeFlag;
	float elapsed;

	begin = clock();

	printf("Limit:%llu\n", ULLONG_MAX);
	
	isPrimeFlag = isPrime_L1( strtoull(argv[1], NULL, 10) );

	end = clock();
	elapsed = ((float)end - (float)begin) / (float)(CLOCKS_PER_SEC);

	if(isPrimeFlag)
		printf("%s is prime.(L1)\n", argv[1]);
	else
		printf("%s is NOT prime.(L1)\n", argv[1]);

	printf("Elapsed time: %.10f\n\n", elapsed );

	return EXIT_SUCCESS;
}


bool isPrime_L1(unsigned long long int n)
{
	unsigned long long divisor;

	divisor = 5; 

	if( n <= 3 )
		return true;
	else if( n%2 == 0 || n%3 == 0)// is not prime if can be divided by 2 or 3
		return false;
	else
		while(divisor <= n/2)
			if( n%divisor == 0 )
				return false;
			else
				divisor++;
	return true;
}
