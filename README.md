# Primes
This is a project created with the purpose of studying prime numbers. It's a work in progress but so far here's what I've found and created:

* isPrime function: fastest known algorithm so far (in this project) to test primality.
* piFunction: tells you how many primes there are before any given n (inclusive). Take **ULLONG_MAX** from **limits.h** as the max value this function can take.
* storePrimes: a function to find primes and register them in a plain text file.
* loadPrimes: loads all the possible primes from a given list until a memory limit is reached.
* isPrime_L1: slowest and siplest primality test algorithm.
* isPrime_L2: a little faster than isPrime_L1.
* nthPrime: gives you the nth prime, e.g. for input 5, it returns 11, the 5th prime.
* isPrimeWList: uses a pre-computed list, could be using loadPrimes, to test primality.

#### Remarks
* Greatest prime found: 3004602589
* Max amount of primes stored: 144660217
* Size of file where they're stored: 1.0 GB
* Hours to find them: 28.15 
* Greatest prime testes in 52 seconds: 18446744003700551681
* Mathematical forms to use to find primes:
	* divisor <= **n/2**
	* divisor <= square root of **n**
	* **6k +- 1** <= square root of **n**

##### Goals and future steps:

* Find a pure mathematical way to test primes faster.
* Store as many primes as possible.
* Find primes greater than **ULLONG_MAX**.