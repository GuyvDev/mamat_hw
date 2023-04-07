#!/bin/bash
urls=$(wget -O- https://www.ynetnews.com/category/3082 | \
	grep -Eo "https://www.ynetnews.com/article/[a-zA-Z0-9./?=_%:-]*" | \
	sort -u)
echo "$urls" | wc -l > results.csv;
echo "$urls" | while read line
do
    netanyahu_count=$(wget -O- $line | grep -o "Netanyahu" | wc -l)
    gantz_count=$(wget -O- $line | grep -o "Gantz" | wc -l)
    bennett_count=$(wget -O- $line | grep -o "Bennett" | wc -l)
    peretz_count=$(wget -O- $line | grep -o "Peretz" | wc -l)

    if [ $netanyahu_count -eq 0 ] && [ $gantz_count -eq 0 ] && \
       [ $bennett_count -eq 0 ] && [ $peretz_count -eq 0 ]
    then
        echo "$line, -" >> results.csv
    else
        echo "$line, Netanyahu, $netanyahu_count, Gantz, $gantz_count," \
	"Bennett, $bennett_count, Peretz, $peretz_count" >> results.csv
    fi
done
