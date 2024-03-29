#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>

#define N 20



long long int X[2^20] = { 1, 2, 3 };
long long int Y[1000000];

// populate X with random values from 1 - 100.

extern long long int asmfunctionthatdoesprocess(X, Y);

// should return a vector/array
long long int c_function_that_does_process(X, Y) {
	// do A * X
	// then do (A * X) + Y
	// return result
}


int main(int argc, char* argv[]) {
	long long int a1, a2, a3, ans;


	long long int result_asm = asmfunctionthatdoesprocess(X, Y);
	long long int result_c = c_function_that_does_process(X, Y);

	// result_asm == result_c SHOULD BE TRUE !!!


	return 0;
}