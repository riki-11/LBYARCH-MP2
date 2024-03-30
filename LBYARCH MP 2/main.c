#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

// Contains DAXPY operation for C
#include "daxpy.h"

//#define N 67108864 // 2^26
#define N 16777216 // 2^24
//#define N 1048576  // 2^20


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

static void checkAccuracy(double Z[], double Z_1[], int size) {
	int i, a_counter = 0; // Innaccuracy counter

	for (i = 0; i < size; i++) {
		if (Z[i] != Z_1[i]) {
			a_counter++;
		}
	}
	if (a_counter > 0)
		printf("x86-64 kernel output is incorrect %d times", a_counter);
	else
		printf("86-64 kernel output is correct");
}

int main(int argc, char* argv[]) {
	int i;
	float a = 2.0;
	double total_timeC = 0;
	clock_t start, end;

	srand(123); // Seed for reproducibility

	// Populate X and Y
	fillArray(X, N);
	fillArray(Y, N);

	// Execute 30 times for testing
	for (i = 0; i < 30; i++) {

		start = clock();			// Clock start time
		daxpy(a, X, Y, Z, N);		// Perform DAXPY for C
		end = clock();				// Clock end time

		/* PUT ASSEMBLY OPERATIONS*/


		/* TOTAL TIME FOR BOTH */
		total_timeC = total_timeC + ((double)(end - start)) / CLOCKS_PER_SEC; // Calculate total time in seconds
	}


	for (int i = 0; i < 10; i++) {
		printf("%.2f | %.2f = %.2f\n", X[i], Y[i], Z[i]);
	}


	printf("Average time: %f", total_timeC/30.0);
	return 0;
}