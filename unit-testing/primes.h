#ifndef PRIMES_H_
#define PRIMES_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

void firstNPrimes(unsigned long long n, char *fileName, unsigned int block);
void primesInTime(unsigned int timeInSeconds, char *fileName, unsigned int block);

unsigned long long nthPrime(unsigned long long top);
unsigned long long piFunction(unsigned long long n);
unsigned long long *primesInMemory(unsigned long long megaBytes);

bool isPrime(unsigned long long int n);

#endif
