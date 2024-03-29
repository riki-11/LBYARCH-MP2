#ifndef DAXPY_H
#define DAXPY_H


// Calculate A*X+Y for all values of X and Y
// Store values in array Z
static void daxpy(double a, double x[], double y[], double Z[], int N) {
    double result_z;
    for (int i = 0; i < N; i++) {
        result_z = a * x[i] + y[i];
        Z[i] = result_z;
    }
}

#endif /* DAXPY_H */
