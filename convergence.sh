#!/bin/bash

convergence_test() {
    n=100
    nmax=${4:?Must provide max number of iterations}  # 1e8
    outfile=${1:?Must provide filename}
    binary=${2:?Must provide binary name}
    flags=${3:?Must provide flags}
    while (( $n <= $nmax ));do
        ./$binary $flags -p $n >> "$outfile"
        n=$(expr $n '*' 10)
    done
}

trapfile='trapezoid_convergence.dat'
montecarlofile='montecarlo_convergence.dat'
touch "$trapfile"
touch "$montecarlofile"
echo "## Trapezoid rule convergence test" > "$trapfile"
echo -e '# n\t%error\ttime' >> "$trapfile"

echo "## Monte carlo method convergence test" > "$montecarlofile"
echo -e "# n\t%error\ttime" >> "$montecarlofile"

make serial
convergence_test "$trapfile" "a.out" '-t' 10000000  # 1e7
convergence_test "$montecarlofile" "a.out" '-m' 1000000000  # 1e9
