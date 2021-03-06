#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include "integrate.h"
#include "timer.h"

const float PIf = 4.0f * atanf(1.0f);
const float x0f = -PIf/2.0f;
const float xnf = PIf/2.0f;
const double PI = 4.0l * atan(1.0l);
const double x0 = -PI/2.0l;
const double xn = PI/2.0l;
const int n = 1000000;

#define HLPMSG "Usage: ./<binary> -t/m <-n num_threads>\n"


enum Precision {
    FLOAT,
    DOUBLE
};


int
main(int argc, char *argv[]) {
    enum Integrator method;
    enum Precision precision = DOUBLE;  // default precision
    if (argc == 1) {
        fprintf(stderr, HLPMSG);
        exit(4);
    }
    int argnum = 1;
    while (argnum < argc) {
        if (argv[argnum][0] == '-')
            switch (argv[argnum][1]) {
                case('t'):
                    // set integration method to trapezoid
                    method = TRAPEZOID;
                    argnum++;
                    break;

                case('m'):
                    // set integration method to montecarlo
                    method = MONTECARLO;
                    argnum++;
                    break;

                case('n'):
                    // set number of threads after
                    // checking for inclusion of omp.h
                    if (argnum == argc-1) {
                        fprintf(stderr, HLPMSG);
                        exit(1);
                    }
#                   ifdef _OPENMP
                    omp_set_num_threads((int)(strtol(argv[argnum+1],NULL,10)));
                    argnum += 2;
#                   endif
#                   ifndef _OPENMP
                    fprintf(stderr, "omp.h has not been included.\n");
                    exit(2);
#                   endif
                    break;
                case('f'):
                    precision = FLOAT;
                    argnum++;
                    break;
                default:
                    fprintf(stderr, "Unrecognized option %s\n", argv[argnum]);
                    exit(3);
            }
    }

    double result;
    double start_time, end_time;
    if (precision == DOUBLE) {
                switch(method) {
            case(TRAPEZOID):
                start_time = get_wall_time();
                result = trapezoid(cos, x0, xn, n);
                end_time = get_wall_time();
                break;
            case(MONTECARLO):
                start_time = get_wall_time();
                result = montecarlo(cos, x0, xn, n);
                end_time = get_wall_time();
                break;
            default:
                fprintf(stderr, "Bro... no\n");
                exit(100);
        }
    } else {
        switch(method) {
            case(TRAPEZOID):
                start_time = get_wall_time();
                result = trapezoidf(cosf, x0f, xnf, n);
                end_time = get_wall_time();
                break;
            case(MONTECARLO):
                start_time = get_wall_time();
                result = montecarlof(cosf, x0f, xnf, n);
                end_time = get_wall_time();
                break;
            default:
                fprintf(stderr, "Bro... no\n");
                exit(100);
        }
    }

    printf("The result of numerical integration is %lf\n", result);
    printf("Time taken (a.u) is %lf\n", end_time - start_time);
    return 0;
}
