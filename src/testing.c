#include "integrate.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include "testing.h"
#include "timer.h"


testing_t
testTiming
(double (*func)(double), enum Integrator method, 
 double x0, double xn, int n, int num_tests){
    int buffer_size = num_tests * sizeof(double);
    double *execution_times = (double *) malloc(buffer_size);
    double result, result_deviation;
    double average_execution_time, start_time, end_time, time_deviation;
    if (method == TRAPEZOID) {
        for (int i = 0; i < num_tests; i++) {
            start_time = get_wall_time();
            result = trapezoid(func, x0, xn, n);
            end_time = get_wall_time();
            execution_times[i] = end_time - start_time;
        }
        result_deviation = 0.0l;

    } else if (method == MONTECARLO) {
        double *result_samples = (double *) malloc(buffer_size);
        for (int i = 0; i < num_tests; i++) {
            start_time = get_wall_time();
            result_samples[i] = montecarlo(func, x0, xn, n);
            end_time = get_wall_time();
            execution_times[i] = end_time - start_time;
        }
        result = average(result_samples, num_tests);
        result_deviation = stddev(result_samples, num_tests);
        free(result_samples);
    }
    average_execution_time = average(execution_times, num_tests);
    time_deviation = stddev(execution_times, num_tests);
    return (testing_t) {result, average_execution_time, result_deviation, time_deviation};
    free(execution_times);
} 


double
average(double *array, int n) {
    double sum = 0.0l;
#   pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += array[i];
    }
    return sum / n;
}

double
stddev(double *array, int n) {
    if (n == 1) return 0.0l;
    double avg = average(array, n);
    double sum = 0.0l;
#   pragma omp parallel for reduction(+:sum);
    for (int i = 0; i < n; i++) {
        sum += (array[i] - avg) * (array[i] - avg);
    }
    sum /= (n-1);
    return sqrt(sum);
}
