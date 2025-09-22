/*
    Luca D'Altri - 20751761
    Project 60, Question 2
    
    This program takes in an integer n. Then it finds and prints the first
    prime p > n that is a Sophie Germain prime (2*p+1 prime too).
    https://en.wikipedia.org/wiki/Safe_and_Sophie_Germain_primes

    Test case #1:
    n = 1
    p = n+1 = 2 is prime *
    2*p+1 = 5 is prime **
    ==> 2 is a Sophie Germain prime

    Test case #2:
    n = 80
    p = n+1 = 81 is not prime
    p = n+2 = 82 is not prime
    p = n+3 = 83 is prime *
    2*p+1 = 167 is prime **
    ==> 83 is a Sophie Germain prime
    
    Test case #3:
    n = 6
    p = n+1 = 7 is prime *
    2*p+1 = 15 is not prime
    p = n+2 = 8 is not prime
    p = n+3 = 9 is not prime
    p = n+4 = 10 is not prime
    p = n+5 = 11 is prime *
    2*p+1 = 23 is prime **
    ==> 11 is a Sophie Germain prime

    Test case #4:
    n = 100,000,000,000,000,000
    p = 100,000,000,000,000,181 is prime *
    2*p+1 = 200,000,000,000,000,363 is prime **
    ==> 100,000,000,000,000,181 is a Sophie Germain prime

*/

#include <math.h> 
#include <stdio.h>

int isPrime(unsigned long long int m);

int main(void) {
    unsigned long long int n, p; //It runs reasonably fast on server until 10^17
    unsigned int i;

    //1. Read a natural integer n
    do {
        printf("Please enter a natural integer n:\n");
        if (scanf("%llu", &n) != 1) {
            fprintf(stderr, "Couldn't read [%llu]\n", n);
            return 1;
        }        
        if (n < 0) {
            fprintf(stderr, "n cannot be negative\n");
        }
    } while (n < 0);

    //2. Check if p > n is a Sophie Germain prime
    for (i = 1; i <= 4294967295; i++) {
        p = n + i;
        if (isPrime(p) == 1 && isPrime(2*p+1) == 1) {
            printf("%llu is the first Sophie Germain prime > n\n", p);
            break;
        }
    }
    
    return 0;
}

int isPrime(unsigned long long int m) {
    if (m == 1) { //Special case
        return 0; 
    }
    for (unsigned long int i = 2; i <= sqrt(m); i++) {
        if (m % i == 0) {
            return 0; //Not prime
        }
    }
    return 1; //Prime
}