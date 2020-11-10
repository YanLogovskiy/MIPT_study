#include <stdio.h>
#include <stdlib.h>
#include <math.h>

enum Num {
	ISIZE = 1000,
	JSIZE = 1000,
	IN = 3,
	JN = 4,
};

int main(int argc, char **argv) {
    double a[ISIZE][JSIZE];
    int i, j;
    FILE *ff;

    for (i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            a[i][j] = 10 * i + j;
        }
    }
    for (i = 0; i < ISIZE - IN; i++) {
        for (j = JN; j < JSIZE; j++) {
            a[i][j] = sin(0.00001 * a[i + IN][j - JN]);
        }
    }

    ff = fopen("result.simple.txt", "w");
    for(i = 0; i < ISIZE; i++) {
        for (j = 0; j < JSIZE; j++) {
            fprintf(ff, "%f ", a[i][j]);
        }
        fprintf(ff, "\n");
    }
    fclose(ff);

    return 0;
}

