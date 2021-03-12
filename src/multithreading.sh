#!/bin/bash

if [[ -z "$1" ]];then
    echo "Must provide one argument" && exit
fi

throughput_test() {
    num_samples=${1:? "Must provide number of samples"}
    outfile=${2:?"Must provide filename"}
    flags=${3:?"Must provide flags"}
    binary=${4:?"Must provide binary name"}
    ./binary "$flags" "-n 1" >> "$outfile"  // serial
    for (( n = 2; n <= 8; n += 2 ))
    do
       ./$binary "-p $num_samples" "$flags" "-n $n" >> "$outfile"
    done
}

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

make parallel
throughput_test "1000000" "$trapfile" "-t" "$bindir/omp.out"
throughput_test "1000000000" "$montecarlofile" "-m" "$bindir/omp.out"

plot_cmd="set terminal png size 1280,960 font \"Source Code Pro,20\"
set border lw 1.5
set output \"$datdir/trapezoid_omp.png\"
set title \"OpenMP Performance - Trapezoid Method\"
set xlabel \"Number of threads\"
set ylabel \"Execution time\"
set style line 1 lc rgb \"red\" pt 7 ps 1.5
set style line 2 lc rgb \"blue\" pt 7 ps 1.5
plot $trapfile u 1:6 ls 1
set output \"$datdir/montecarlo_omp.png\"
set title \"OpenMP Performance - Monte Carlo Method\"
plot $montecarlofile u 1:6 ls 2
"

