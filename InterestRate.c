/*
    Luca D'Altri

    This program takes in:
    A : initial investment, assuming possible to invest fractions of unit
    R : % of yearly compound interest rate
    
    And computes:
    A(1+R/100)^N : how much is A worth at the end of year N, printing to
    screen the result of years 1-15. Values rounded off to two places.
*/

#include <math.h>
#include <stdio.h>

#define END 15

int main(void) {
    double A, R, value[END];
    int i;

    //1. Read A, R and check if both non-negative
    do {
        printf("Please enter A = initial investment amount:\n");
        scanf("%lf", &A);
        if (A < 0.0) {
            fprintf(stderr, "A not valid: cannot invest negative amounts\n");
        }
    } while (A < 0.0);

    do {
        printf("Please enter R = %% of compound interest rate:\n");
        scanf("%lf", &R);
        if (R < 0.0) {
            fprintf(stderr, "R not valid: the interest rate cannot be negative\n");
        }
    } while (R < 0.0);

    //2. Compute and print the value of the investment A from year 1 to 15
    for (i = 1; i <= END; i++) {
        value[i-1] = A*pow(1+(R/100), i);
        printf("Yr: %d\tVal: %.2lf\n", i, value[i-1]);
    }

    return 0;
}


