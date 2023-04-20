#!/bin/bash
file=./"$1".txt
if [ "$#" -ne 1 ]; then
    echo "Worng number of arguments" >&2
    exit
elif [ ! -f "$file" ]; then
    echo "Course not found" >&2
    exit
else
    rm -r ./"$1"_stat 2> /dev/null
    mkdir ""$1"_stat"
    echo -ne "$(./hist.exe "$file")\n" >> "./"$1"_stat/histogram.txt"
    for prog in mean.exe median.exe min.exe max.exe; do
        echo -ne "$(./"$prog" "$file")\t" >> "./"$1"_stat/statistics.txt"
    done
    pass_failed=($(./hist.exe "$file" -n_bins 11 | awk '{print $2}'));
    for i in {0..10}; do
        # From 6th place and onwards, all scores are above 55
        if [[ "$i" -gt 5 ]]; then
            pass=$((pass_failed[i] + pass))
        fi
        sum=$((pass_failed[i] + sum))
    done
    pass=$(("$pass"*100 / sum));
    echo -ne "$pass%\n" >> "./"$1"_stat/statistics.txt";
fi