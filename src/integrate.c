#include "integrate.h"
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>

float
trapezoidf(float (*func)(float x), float x0, float xn, int n)
{
    const float h = (xn - x0)/n;
    float sum = (func(x0) + func(x0 + n*h))/2.0f;
#   pragma omp parallel for reduction(+:sum)
    for (int i = 1; i < n; i++)
        sum += func(x0 + i*h); 

    sum *= h;
    return sum; 
}


double
trapezoid(double (*func)(double x), double x0, double xn, int n) {
    double h = (xn - x0)/n;
    double sum = (func(x0) + func(x0 + n*h))/2.0l;
#   pragma omp parallel for reduction(+:sum)
    for (int i = 1; i < n; i++)
        sum += func(x0 + i*h);
    
    sum *= h;
    return sum;
}


double
montecarlo(double (*func)(double x), double x0, double xn, int n) {
    const double scale = (xn - x0);

    struct drand48_data rand_buff;  // RNG state buffer
    double random_double;
    double approx = 0.0l;
#   pragma omp parallel for private(rand_buff, random_double)\
    reduction(+:approx)
    for (int i = 0; i < n; i++) {
        int drand_err = drand48_r(&rand_buff, &random_double);  // [0.0, 1.0)
        if (drand_err) {
            fprintf(stderr, "Call to `drand48_r` failed!\n");
            exit(10);
        }
        approx+= func(scale * random_double + x0);
    }
    return (approx / n) * scale;
}



float
montecarlof(float (*func)(float x), float x0, float xn, int n) {
    const float scale = (xn - x0);

    struct drand48_data rand_buff;  // RNG state buffer
    double random_double;
    float approx = 0.0;
#   pragma omp parallel for private(rand_buff, random_double)\
    reduction(+:approx)
    for (int i = 0; i < n; i++) {
        int drand_err = drand48_r(&rand_buff, &random_double);
        if (drand_err) {
            fprintf(stderr, "Call to `drad48_r` failed!\n");
            exit(10);
        }
        approx += func(scale * ((float)random_double) + x0);
    }
    return (approx / n) * scale;
}
