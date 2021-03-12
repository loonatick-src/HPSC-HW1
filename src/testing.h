#ifndef _MY_TESTING_H
#define _MY_TESTING_H

typedef struct {
    double result;
    double execution_time;
    double result_deviation;
    double time_deviation;
} testing_t;


testing_t
testTiming
(double (*func)(double), enum Integrator method,
 double x0, double xn, int n, int num_tests);


double average(double *array, int n);


double stddev(double *array, int n);
#endif
