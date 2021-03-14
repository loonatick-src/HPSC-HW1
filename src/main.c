#include <assert.h>
#include <math.h>
#include <omp.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/times.h>
#include "integrate.h"
#include "timer.h"
#include "testing.h"

const float PIf = (float) M_PI;
const float x0f = -PIf/2.0f;
const float xnf = PIf/2.0f;
const double PI = M_PI;
const double x0 = -PI/2.0l;
const double xn = PI/2.0l;
const double analytical_result = 2.0l;
int n = 1000000;

#define HLPMSG "Usage: ./<binary> -t/m[s] [-n num_threads]\
[-p num_samples]\n"


int
main(int argc, char *argv[]) {

    enum Integrator method = NONE;
    int num_stats = 1;
#   ifdef _OPENMP
    int num_threads = 1;
#   endif

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
                    if (argv[argnum][2] != 's')
                        argnum++;
                    else {
                        num_stats = (int) strtol(argv[argnum+1], NULL, 10);
                        // fprintf(stderr, ">>>%d<<<\n", num_stats);
                        assert(num_stats > 1);
                        argnum += 2;
                    }
                    break;

                case('m'):
                    // set integration method to montecarlo
                    method = MONTECARLO;
                    if (argv[argnum][2] != 's')
                        argnum++;
                    else {
                        num_stats = (int) strtol(argv[argnum+1], NULL, 10);
                        // fprintf(stderr, ">>>%d<<<\n", num_stats);
                        assert(num_stats > 1);
                        argnum += 2;
                    }
                    break;

                case('n'):
                    // set number of threads after
                    // checking for inclusion of omp.h
#                   ifdef _OPENMP
                    num_threads = (int)(strtol(argv[argnum+1],NULL,10));
                    omp_set_num_threads(num_threads);
                    argnum += 2;
#                   endif
#                   ifndef _OPENMP
                    fprintf(stderr, "omp.h has not been included.\n");
                    exit(2);
#                   endif
                    break;
                case('p'):
                    n = (int) strtol(argv[argnum+1],NULL,10);
                    argnum+=2;
                    break;
                default:
                    fprintf(stderr, "Unrecognized option %s\n", argv[argnum]);
                    exit(3);
            }
    }
    assert(method != NONE);

    testing_t results = testTiming(cos, method, x0, xn, n, num_stats);
    double error = fabs(results.result - analytical_result);
    double percent_error = error * 50;

#ifndef _OPENMP
    printf("%d %lf %lf %lf %lf %lf\n", n, results.result, results.result_deviation, percent_error, results.execution_time, results.time_deviation);
#endif

#ifdef _OPENMP
    printf("%d %d %lf %lf %lf %lf %lf\n", num_threads, n, results.result, results.result_deviation, percent_error, results.execution_time, results.time_deviation);
#endif
    return 0;
}
