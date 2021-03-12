#ifndef INTEGRATE_H
#define INTEGRATE_H
enum Integrator {
    NONE,
    TRAPEZOID,
    MONTECARLO,
};

float trapezoidf
(float (* func)(float x), float x0, float xn, int n);

double trapezoid
(double (*func)(double x), double x0, double xn, int n);

float montecarlof
(float (*func)(float x), float x0, float xn, int n);

double montecarlo
(double (*func)(double x), double x0, double xn, int n);
#endif
