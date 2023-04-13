#!/bin/bash
shopt -s expand_aliases; alias wg="wget --no-check-certificate -q -O-";
urls=$(wg https://www.ynetnews.com/category/3082 | \
	grep -oP "https://(www.)?ynetnews.com/article/[a-zA-Z0-9]+" | \
	sort -u) 
print+="$(echo "$urls" | wc -l)"
echo "$urls" | ( while read line
do
    # In order to count all names with "uniq -c", we added each one of them once 
    # at the end, we decreased them respectively otherwise, we won't be able to
    # distinguish the counting order in the array
    arr=($(wg "$line"| cat - <(echo "Netanyahu Gantz Bennett Peretz")|\
            grep -oE 'Gantz|Netanyahu|Bennett|Peretz' | \
            sort -d | uniq -c | awk '{print $1}'))

    # In case the array contains only 1, it is just our adding, 
    # therefore the page didn't contain these names orginally
    if [[ "${arr[*]}" == $'1 1 1 1' ]]; then 
        print+="\n$line, -"
    else
        print+="\n$line, Netanyahu, $((${arr[2]}-1)), Gantz, $((${arr[1]}-1)),"\
	    print+=" Bennett, $((${arr[0]}-1)), Peretz, $((${arr[3]}-1))"
    fi
    unset arr;
done
echo -e "$print" > results.csv;) 
