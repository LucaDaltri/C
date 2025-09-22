/*
    Luca D'Altri - 20751761
    Project 60, Question 3
    
    This program calculates <B>: the number of walks of length <= <n> of a given graph:
    B = A + A^2 + A^3 + ... + A^n
    Where <n> is taken by the user and the graph (matrix <A>) is a 5x5 matrix taken
    from matrix.txt.
    The program prints <B> to walks.txt and how many entries of <B> are = 0 to the screen.
    The special case n = 0 is considered, returning B = A^0 = the identity matrix.

        (Note that A must be able to take in negative integers, while the other matrices don't
        need this. Furthermore, other matrices must be able to store very large integers because 
        of the exponential process - This is not intended to be a real comment but it's just 
        an explanation of my choice of long long unsigned int for <A^p>, <tmp>, <B> VS int for <A>.
        *** At the end of the code there is a working version with functions.)
*/

#include <stdio.h>

#define DIM 5

int main(void) {
    long long unsigned int ap[DIM][DIM], tmp[DIM][DIM], b[DIM][DIM];
    int a[DIM][DIM], i, j, k, n, pow, zero;
    FILE *matrix_file, *walks_file;

    //1. Read <n> and check if natural
    do {
        printf("Please enter the walks length <n>:\n");
        scanf("%d", &n);
        if (n < 0)
            fprintf(stderr, "<n> not valid: it must be >= 0\n");
    } while (n < 0);

    //2. Open input/output text files
    matrix_file = fopen("matrix.txt", "r");
    if (matrix_file == NULL) {
        fprintf(stderr, "Couldn't open matrix.txt\n");
        return 1;
    }
    walks_file = fopen("walks.txt", "w");
    if (walks_file == NULL) {
        fprintf(stderr, "Couldn't open walks.txt\n");
        return 1;
    }

    //3. Read matrix.txt (check if there are entries <= 0)
    for (i = 0; i < 5; i++) {
        for (j = 0; j < 5; j++) {
            fscanf(matrix_file, "%d", &a[i][j]);
            if (a[i][j] < 0) {
                fprintf(stderr, "Entry [%d][%d] = %d < 0. Entries cannot be negative\n", i, j, a[i][j]);
                return 1;
            }
        }
    }
    fclose(matrix_file); 
    
    //4. Initialize <tmp> and <B>
    if (n == 0) { //special case: n = 0
        for (i=0; i<DIM; i++) {
            for (j=0; j<DIM; j++) {
                if (i == j) {
                    b[i][j] = 1;  
                }
                else {
                    b[i][j] = 0;
                }
            }
        }
    } else {
        for (i=0; i<DIM; i++) {
            for (j=0; j<DIM; j++) {
                tmp[i][j] = a[i][j];
                b[i][j] = a[i][j];
            }
        }
    }

    //5. Compute matrix <B>: the number of walks of length <= n
    for (pow = 2; pow <= n; pow++) { //start from from computing A^2 (power p = 2)
        for (i = 0; i < DIM; i++) {
            for (j = 0; j < DIM; j++) {
                ap[i][j] = 0;
                for (k = 0; k < DIM; k++) {
                    ap[i][j] += tmp[i][k]*a[k][j];
                }
            }
        }
        for (i = 0; i < DIM; i++) { //update tmp and B
            for (j = 0; j < DIM; j++) {
                tmp[i][j] = ap[i][j];
                b[i][j] += ap[i][j];
            }
        }            
    }

    //6. Print <B> to walks.txt, and how many zero entries <B> has
    zero = 0;
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            if (j == 4) {
                fprintf(walks_file, "%llu\n", b[i][j]);
            } else {
                fprintf(walks_file, "%llu\t", b[i][j]);
            }
            if (b[i][j] == 0) {
                zero++;
            }
        }
    }
    fclose(walks_file);
    printf("B has %d zero entries\n", zero);

    return 0;
}

/*

//Verison beta, with functions

#include <stdio.h>

#define DIM 5

int negativityCheck(int matrix[DIM][DIM], FILE* matrix_file);

void getB(int matrix[DIM][DIM], long long unsigned int matrix2[DIM][DIM], int n);

void printAndWrite(long long unsigned int b[DIM][DIM], FILE* walks_file);

int main(void) {
    int a[DIM][DIM], n;
    long long unsigned int b[DIM][DIM];
    FILE *matrix_file, *walks_file;

    //1. Read <n> and check if natural
    do {
        printf("Please enter the walks length <n>:\n");
        scanf("%d", &n);
        if (n < 0)
            fprintf(stderr, "<n> not valid: it must be >= 0\n");
    } while (n < 0);

    //2. Open input/output text files
    matrix_file = fopen("matrix.txt", "r");
    if (matrix_file == NULL) {
        fprintf(stderr, "Couldn't open matrix.txt\n");
        return 1;
    }
    walks_file = fopen("walks.txt", "w");
    if (walks_file == NULL) {
        fprintf(stderr, "Couldn't open walks.txt\n");
        return 1;
    }

    //3. Read matrix.txt (check if there are entries <= 0)
    if (negativityCheck(a, matrix_file) == 1) {
        return 1;
    }
    fclose(matrix_file);
    
    //4. Get the number of walks matrix <B>
    getB(a, b, n);

    //5. Print <B> to walks.txt, and how many zero entries <B> has
    printAndWrite(b, walks_file);
    fclose(walks_file);

    return 0;
}

int negativityCheck(int matrix[DIM][DIM], FILE* matrix_file) {
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            fscanf(matrix_file, "%d", &matrix[i][j]);
            if (matrix[i][j] < 0) {
                fprintf(stderr, "Entry [%d][%d] = %d < 0. Entries cannot be negative\n", i, j, matrix[i][j]);
                return 1;
            }
        }
    }
    return 0;
}

void getB(int a[DIM][DIM], long long unsigned int b[DIM][DIM], int n) {
    long long unsigned int ap[DIM][DIM], tmp[DIM][DIM];
    int i, j, k, pow;

    //Initialize <tmp> and <B>
    if (n == 0) { //special case: n = 0
        for (i=0; i<DIM; i++) {
            for (j=0; j<DIM; j++) {
                if (i == j) {
                    b[i][j] = 1;  
                }
                else {
                    b[i][j] = 0;
                }
            }
        }
    } else {
        for (i=0; i<DIM; i++) {
            for (j=0; j<DIM; j++) {
                tmp[i][j] = a[i][j];
                b[i][j] = a[i][j];
            }
        }
    }

    //Compute the matrix <B>: the number of walks of length <= n
    for (pow = 2; pow <= n; pow++) { //start from from computing A^2 (power p = 2)
        for (i = 0; i < DIM; i++) {
            for (j = 0; j < DIM; j++) {
                ap[i][j] = 0;
                for (k = 0; k < DIM; k++) {
                    ap[i][j] += tmp[i][k]*a[k][j];
                }
            }
        }
        for (i = 0; i < DIM; i++) { //update tmp and B
            for (j = 0; j < DIM; j++) {
                tmp[i][j] = ap[i][j];
                b[i][j] += ap[i][j];
            }
        }            
    }
}

void printAndWrite(long long unsigned int b[DIM][DIM], FILE* walks_file) {
    int i, j, zero;
    zero = 0;
    for (i = 0; i < DIM; i++) {
        for (j = 0; j < DIM; j++) {
            if (j == 4) {
                fprintf(walks_file, "%llu\n", b[i][j]);
            } else {
                fprintf(walks_file, "%llu\t", b[i][j]);
            }
            if (b[i][j] == 0) {
                zero++;
            }
        }
    }
    fclose(walks_file);
    printf("B has %d zero entries\n", zero);
}

*/