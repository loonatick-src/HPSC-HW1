#!/bin/bash

#if [[ -z "$1" ]];then
#    echo "Must provide one argument" && exit
#fi

bindir="../bin"
datdir="../dat"
trapfile="$datdir/trapezoid_throughput.dat"
montecarlofile="$datdir/montecarlo_throughput.dat"
touch "$trapfile" && touch "$montecarlofile"

headers="# #1_num_threads\t#2_n\t#3_result\t#4_deviation\t#5_percent_error\t#6_execution_time\t#7_time_deviation"
echo "## multithreaded trapezoid rule timing results" > "$trapfile"
echo -e "$headers" >> "$trapfile"

echo "## multithreaded monte carlo rule timing results" > "$montecarlofile"
echo -e "$headers" >> "$montecarlofile"

throughput_test() {
    num_samples=${1:? "Must provide number of samples"}
    outfile=${2:?"Must provide filename"}
    flags=${3:?"Must provide flags"}
    for (( n = 2; n <= 8; n += 2 ))
    do
        echo "Running with $n threads..."
        cmd="../bin/omp.out -p $num_samples $flags -n $n"
        echo $cmd
        $cmd >> "$outfile"
    done
}

num_stats="5"

make parallel
echo "starting throughput tests for trapezoid method"
throughput_test "1000000" "$trapfile" "-ts $num_stats" "$bindir/omp.out"
echo "starting throughput tests for Monte Carlo method"
throughput_test "100000000" "$montecarlofile" "-ms $num_stats" "$bindir/omp.out"
echo "Done with throughput tests"


plot_cmd="set terminal png size 1280,960 font \"Source Code Pro,20\"
set border lw 1.5
set key box
set grid
set output \"$datdir/trapezoid_omp.png\"
set title \"OpenMP Performance - Trapezoid Method\"
set xlabel \"Number of threads\"
set ylabel \"Execution time\"
set style line 1 lc rgb \"red\" pt 7 ps 1.5
set style line 2 lc rgb \"blue\" pt 7 ps 1.5
plot \"$trapfile\" u 1:6 ls 1 title \"Trapezoid Method (Average of $num_stats runs)\" w lp
set output \"$datdir/montecarlo_omp.png\"
set title \"OpenMP Performance - Monte Carlo Method\"
plot \"$montecarlofile\" u 1:6 ls 2 title \"Monte Carlo Method (Average of $num_stats runs)\" w lp
"

plot_script="omp_plot.gp"
echo "$plot_cmd" > "$plot_script"
echo "Creating plots..."
gnuplot "$plot_script"
rm "$plot_script"
echo "Done"
