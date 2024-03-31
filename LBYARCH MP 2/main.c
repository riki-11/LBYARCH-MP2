#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <time.h>

// Contains DAXPY operation for C
#include "daxpy.h"


// Import ASM functions
extern void scalarMultiply(long long int vectorSize, double origVector[], double resultVector[], double a);
extern void vectorAddition(long long int vectorSize, double vector1[], double vector2[]);

//#define N 67108864 // 2^26
#define N 16777216 // 2^24
//#define N 1048576  // 2^20

double X[N];
double Y[N];
double Z_C_kernel[N]; // Where Results for DAXPY is stored (For kernel C)
double Z_ASM_kernel[N]; // Results for DAXPY is stored (for x86-64 kernel)


static void fillArray(double array[], int size) {
	int i;
	for (i = 0; i < size; i++) {
		array[i] = (double)rand() / RAND_MAX * 100.0; // FIll array with numbers from 0-100
	}
}


static void checkAccuracy(double C[], double ASM[], int size) {
	int i, a_counter = 0; // Innaccuracy counter
	printf("Z VALUES\n");
	printf("    C\t\t\tx86-64\n");

	for (i = 0; i < 10; i++) {
		printf("   %.2f\t | \t%.2f\n", C[i], ASM[i]);
	}


	for (i = 0; i < size; i++) {
		if (C[i] != ASM[i]) {
			a_counter++;
		}
	}
	if (a_counter > 0)
		printf("\nx86-64 kernel output was incorrect %d times", a_counter);
	else
		printf("\n86-64 kernel outputs are correct");
}


// Performs dapxy function 30 times using C kernel
// Returns: average execution time of 30 runs 
static double runCKernelTests(double X[], double Y[], double Z[], float a) {
	int i;
	double current_timeC;
	double total_timeC = 0;
	double avg_timeC;
	clock_t start, end;

	// Execute 30 times for testing
	for (i = 0; i < 30; i++) {
		printf("   %d  \t\t\t", i + 1);

		start = clock();			// Clock start time
		daxpy(a, X, Y, Z, N);		// Perform DAXPY for C
		end = clock();				// Clock end time

		current_timeC = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculate time of current run in seconds
		total_timeC += current_timeC; // Add to total time in seconds
		printf("%f       \t\t\n", current_timeC);
	}

	avg_timeC = total_timeC / 30.0;

	return avg_timeC;
}


// Performs dapxy function 30 times using x86-64 kernel
// Returns: average execution time of 30 runs 
static double runASMKernelTests(double X[], double Y[], double Z[], float a) {
	int i;
	double current_timeASM, avg_timeASM, total_timeASM = 0, d1;
	clock_t start, end;

	for (i = 0; i < 30; i++) {
		printf("   %d  \t\t\t", i + 1);

		start = clock();
		//d1 = *X;
		scalarMultiply(N, X, Z, a);
		vectorAddition(N, Z, Y);
		end = clock();

		current_timeASM = ((double)(end - start)) / CLOCKS_PER_SEC; // Calculate time of current run in seconds
		total_timeASM += current_timeASM; // Add to total time in seconds
		printf("%f       \t\t\n", current_timeASM);
	}

	avg_timeASM = total_timeASM / 30.0;

	return avg_timeASM;
}


int main(int argc, char* argv[]) {
	float a = 2.0;
	double avg_timeC, avg_timeASM;

	srand(123); // Seed for reproducibility

	// Populate X and Y
	fillArray(X, N);
	fillArray(Y, N);

	printf("N = %ld (2^24)\n\n", N);


	printf("Executing 30 tests for C Kernel...\n");
	printf("Test No.\t\tC-Kernel Time\n");
	avg_timeC = runCKernelTests(X, Y, Z_C_kernel, a);
	printf("\n\n---------------------------------------------\n\n");

	printf("Executing 30 tests for x86-64 Kernel...\n");
	printf("Test No.\t\tx86-64 Kernel Time\n");
	avg_timeASM = runASMKernelTests(X, Y, Z_ASM_kernel, a);
	printf("\n\n---------------------------------------------\n\n");

	printf("Running accuracy test ...\n");
	checkAccuracy(Z_C_kernel, Z_ASM_kernel, N);

	printf("\n\n---------------------------------------------\n");
	printf("\nAVERAGE TIMES w/ N = %ld: \n", N);
	printf("C Kernel: %f\n", avg_timeC);
	printf("x86-64 Kernel: %f", avg_timeASM);
	printf("\n\n---------------------------------------------\n\n");



	return 0;
}