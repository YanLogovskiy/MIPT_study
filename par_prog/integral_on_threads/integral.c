#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

float integral = 0, sigma = 0.5;
float START = 0, END = 0.99;
float ACCURACY;
int ThNumber;

struct args {
    float start;
    float end;
};

float func(float x) {
    return cos(1/(1-x));
}

float func_second_derivative(float x) {
    return (2*(x-1)*sin(1/(1-x)) - cos(1/(1-x))) / pow(1 - x, 4);
}

float countError(float x_start, float x_end) {
    float step = 0.00001, max = 0;
    for (float x = x_start; x < x_end; x+=step) {
        float f_2_der = fabs(func_second_derivative(x));
            if(f_2_der > max) {
                max = f_2_der;
            }
    }
    float error = fabs((pow(x_start - x_end, 3) * max) / 12);
    return error;
};

void *thread_routine(void *args) {
    float res = 0, step = 0.01, error = 0;
    float x = ((struct args*)args)->start;
    float end = ((struct args*)args)->end;

    while (x + step <= end) {
        error = countError(x, x + step);
        if (error < ACCURACY) {
            step = step;
        }
        else {
            step = step * sigma;
        }

        if (x + step > ((struct args*)args)->end) {
            break;
        }

        res += ((func(x) + func(x + step))*step)/2;
        x += step;
    }

    if(x < end) {
        step = end - x;
        res += ((func(x) + func(x + step))*step)/2;
        x += step;
    }

    integral += res;
    return NULL;
};

int main(int argc, char** argv) {

    ThNumber = (argc >= 2) ? atoi( argv[1] ) : 4;
    ACCURACY = (argc >= 3) ? atof( argv[2] ) : 0.0001;

    pthread_t *thid = malloc(ThNumber*sizeof(pthread_t));
    struct args *arguments = malloc(ThNumber*sizeof(struct args));

    float zone = END / ThNumber;

    int i = 0;
    time_t clocks_1 = clock();

    for (i = 0; i < ThNumber; i++) {
        if (i == 0) arguments[i].start = START;
        else arguments[i].start = i * zone;
        arguments[i].end = (i + 1) * zone;

        if (pthread_create(&thid[i], (pthread_attr_t *)NULL, thread_routine, (void*)&arguments[i]) != 0) {
            printf("Error while creating a thread\n");
            exit(EXIT_FAILURE);
        }
    }

    for (i = 0; i < ThNumber; i++) {
        pthread_join(thid[i], (void **)NULL);
    }

    time_t clocks = clock() - clocks_1;
    printf("\nintegral = %f, computed by clocks = %ld\n", integral, clocks);

    return 0;
}
