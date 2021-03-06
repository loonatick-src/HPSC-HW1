#include <time.h>
#include <sys/time.h>
#include "timer.h"

double
get_wall_time() {
    struct timeval time;
    if (gettimeofday(&time,NULL)) {
        // error
        return 0;
    }
    return (double)time.tv_sec + (double)time.tv_usec * 0.000001;
}

double get_cpu_time() {
    return (double)clock() / CLOCKS_PER_SEC;
}
