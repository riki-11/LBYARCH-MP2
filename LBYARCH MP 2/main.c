#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

// Contains DAXPY operation for C
#include "daxpy.h"

#define N 2^30


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

int main(int argc, char* argv[]) {
	srand(123);
	float a = 2.0;
	clock_t t;


	// Populate X and Y
	fillArray(X, N);
	fillArray(Y, N);

	t = clock(); // Clock start time
	daxpy(a, X, Y, Z, N); // Perform DAXPY for C
	t = clock() - t; // Clock end time

	double time = ((double)(t)) / CLOCKS_PER_SEC; // Calculate total time

	for (int i = 0; i < 10; i++) {
		printf("%.2f | %.2f = %.2f\n", X[i], Y[i], Z[i]);
	}
	printf("Seconds: %f", time);
	return 0;
}