#!/bin/bash

trapfile='trapezoid_convergence.dat'
touch "$trapfile"
echo "## Trapezoid rule convergence test" > "$trapfile"
echo -e '# n\t%error\ttime' >> "$trapfile"

make serial

# n=10
# nmax=10000000
# while (( $n <= $nmax ));do
    
