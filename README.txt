ME 766 Assignment 1 Submission
Author: Chaitanya Kumar
Roll Number: 170260019  

The source code and header files are in the `src`
directory along with a makefile and bash scripts
for convergence and timing studies. Plots have
been made in the same script using gnuplot.

To build after starting a terminal session
in the current directory and

cd src/
make serial  # create binary for serial code in bin/
make parallel  # create binary for OpenMP code in bin/


The binaries a.out (for serial) and omp.out (for
multithreaded code) will be found in the `bin`
directory. Try `./a.out -h` or `./omp.out -h` to
see information on flags.

e.g. To run the OpenMP binary with 6 threads for
Monte Carlo method, use
`./omp.out -m -n 6`

To run the serial binary for Trapezoid method with
100000 divisions of the interval, use
`./a.out -t -p 100000`. 

To get the average result for 5 iterations for parallel Monte
Carlo method with 12 threads, use
`./omp.out -ms 5 -n 12`

Results of the convergence study are stored in the 
`dat` directory.
