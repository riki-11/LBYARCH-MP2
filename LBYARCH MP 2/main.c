#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

// Contains DAXPY operation for C
#include "daxpy.h"

#define N 3

// Import ASM functions
extern double doublesum(double d1, double d2, double vectorSize);
extern double scalarMultiply(float a, double vector[]);

// Declare Vectors as Arrays
double X[N];
double Y[N];
double Z[N]; // Where Results for DAXPY is stored (For kernel C)

// populate X with random values from 1 - 100.

//extern long long int asmfunctionthatdoesprocess(X, Y);


static void fillArray(double array[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		array[i] = (double)rand() / RAND_MAX * 100.0;
	}
}

static void displayVectorContents(double array[], int size) {
	int i;
	printf("Vector contains: [");
	for (i = 0; i < size; i++) {
		printf("%.2lf, ", array[i]);
	}
	printf("]\n");
}

int main(int argc, char* argv[]) {
	srand(123);
	float a = 2.0;
	clock_t t;


	// Populate X and Y
	printf("Populating Vector X...\n");
	fillArray(X, N);
	displayVectorContents(X, N);
	printf("Populating Vector Y... \n");
	fillArray(Y, N);
	displayVectorContents(Y, N);

	// Execute algorithm for x86-64 Kernel
	printf("\nx86-64 Run:\n");

	// Point the current assembly to the X vector array (IDK WHY WE NEED TO DO THIS)
	double d1 = *X; 

	// Multiply each value in X by A
	double result = scalarMultiply(a, X);
	printf("RESULT: %f\n\n", result);


	// Execute algorithm for C kernel
	printf("\nC Kernel Run\n");
	t = clock(); // Clock start time
	daxpy(a, X, Y, Z, N); // Perform DAXPY for C
	t = clock() - t; // Clock end time

	double time = ((double)(t)) / CLOCKS_PER_SEC; // Calculate total time

	// TODO: change this N to 10 again.
	for (int i = 0; i < N; i++) {
		printf("%.2f | %.2f = %.2f\n", X[i], Y[i], Z[i]);
	}
	printf("Seconds: %f\n", time);




	
	return 0;
}