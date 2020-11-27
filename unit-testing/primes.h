#ifndef PRIMES_H_
#define PRIMES_H_

#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include <math.h>
#include <time.h>

volatile bool LIST_ALL_PRIMES_STOP;

bool isPrime(unsigned long long int n);

bool isPrime2(unsigned long long int n);

bool isPrime_L1(unsigned long long int n);
bool isPrime_L2(unsigned long long int n);
bool isPrimeSqrt(unsigned long long int n);

unsigned long long nthPrime(unsigned long long n);
unsigned long long piFunction(unsigned long long n);

bool isPrime_WList(unsigned long long n, unsigned long long *primeList, unsigned long long listLimit);
unsigned long long* loadPrimes(char *fileName, unsigned long long *memLimit);
void listAllPrimes(char *fileName, unsigned long long memLimit);

#endif
