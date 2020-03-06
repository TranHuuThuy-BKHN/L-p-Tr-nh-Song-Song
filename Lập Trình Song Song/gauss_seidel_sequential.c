#include <stdio.h>
#include <math.h>

#define N 40
#define epsilon 0.0001

void main() {
    int i, j;

    // Initialize a square domain, periodic in x, fixed upper and lower boundaries
    float c[N][N], delta, east, west, south, north, c_1;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            c[i][j] = 0;
        }
    }
    
    void update() {
        // periodic boundaries
        west = (j == 0) ? c[i][N - 1] : c[i][j - 1];
        east = (j == N - 1) ? c[i][0] : c[i][j + 1];
        // fixed boundaries
        south = (i == N - 1) ? 0 : c[i + 1][j];
        north = (i == 0) ? 1 : c[i - 1][j];
        c_1 = c[i][j];
        c[i][j] = 0.25 * (west + east + south + north);
        // stopping criterion
        if (fabs(c[i][j] - c_1) > delta) {
            delta = fabs(c[i][j] - c_1);
        }
    }

    do {
        delta = 0;
        // Update all red grid points
        for (i = 0; i < N; i++) {
            if (i % 2 == 0) {
                for (j = 0; j < N; j = j + 2) {
                    update();
                }
            } else {
                for (j = 1; j < N; j = j + 2) {
                    update();
                }
            }
        }
        // Update all black grid points
        for (i = 0; i < N; i++) {
            if (i % 2 == 1) {
                for (j = 0; j < N; j = j + 2) {
                    update();
                }
            } else {
                for (j = 1; j < N; j = j + 2) {
                    update();
                }
            }
        }
    } while (delta > epsilon);
    
    // Print result
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            printf("%5.2f", c[i][j]);
        }
        printf("\n");
    }
}
