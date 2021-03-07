#!/bin/bash

if [[ -z "$1" ]];then
    echo "Must provide one argument" && exit
fi

throughput_test() {
    echo "Not implemented lol"    
}

trapfile="trapezoid_throughput.dat"
montecarlofile="montecarlo_throughput.dat"
touch "$trapfile" && touch "$montecarlofile"

echo "## multithreaded trapezoid rule timing results" > trapfile
echo -e "# num_threads\t"
