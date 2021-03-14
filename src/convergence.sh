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

datdir="../dat"
bindir="../bin"
trapfile="$datdir/trapezoid_convergence.dat"
serialbin="$bindir/a.out"
montecarlofile="$datdir/montecarlo_convergence.dat"
headers="# #1_n\t#2_results.result\t#3_results.result_deviation\t#4_percent_error\t#5_results.execution_time\t#6_results.time_deviation"

touch "$trapfile"
touch "$montecarlofile"
echo "## Trapezoid rule convergence test" > "$trapfile"
echo -e "$headers" >> "$trapfile"

echo "## Monte carlo method convergence test" > "$montecarlofile"
echo -e "$headers" >> "$montecarlofile"

make serial
convergence_test "$trapfile" "$serialbin" '-t' 10000000  # 1e7
num_stats=5
convergence_test "$montecarlofile" "$serialbin" "-ms $num_stats" 1000000000  # 1e9

conv_plt_script="convergence_plot_script.gp"
plotcmd="set terminal png size 1280,960 font \"Source Code Pro,20\"
set output \"$datdir/convergence_trapezoid.png\"
set key box
set grid
set border lw 1.5
set logscale x
set ylabel \"%Error\"
set xlabel \"n\"
set title \"Convergence Test - Trapezoid Method\"
set style line 1 lc rgb \"red\" pt 7 ps 1.5
set style line 2 lc rgb \"blue\" pt 7 ps 1.5
plot \"$trapfile\" using 1:4 ls 1 title \"Trapezoid Method\" w lp
set logscale y
set output \"$datdir/convergence_trapezoid_log.png\"
plot \"$trapfile\" using 1:4 ls 1 title \"Trapezoid Method\" w lp
unset logscale y
set output \"$datdir/convergence_montecarlo.png\"
set title \"Convergence Test - Monte Carlo Method\"
plot \"$montecarlofile\" using 1:4 ls 2 title \"Monte Carlo Method\" w lp
set logscale y
set output \"$datdir/convergence_montecarlo_log.png\"
plot \"$montecarlofile\" using 1:4 ls 2 title \"Monte Carlo Method - log scale\" w lp
set title \"Monte Carlo Method - Standard Deviation\"
unset logscale y
set ylabel \"Absolute standard deviation\"
set output \"$datdir/standdev_montecarlo.png\"
plot \"$montecarlofile\" using 1:3 ls 2 w lp title \"Standard Deviation for $num_stats runs\"
"


echo "$plotcmd" > "$conv_plt_script"
gnuplot "$conv_plt_script"
rm "$conv_plt_script"
