#!/bin/bash

# Check if there is a valid number of arguments
if [[ $# -ne 1 ]]; then
	echo "Wrong number of arguments" >&2
	exit 1
fi
rules_file=$1

#Reading packets file and rearranging.
packets=$(sed -r '/^$/d' <<< $(sed -r 's/\s+//g' <<< $(cat)))


#Reading rules file and filtering comments, and edited.
rules=$(sed -r '/^#/d' <<< $(sed -r 's/#/\n#/g' <<< $(cat "$rules_file")))
rules=$(sed -r '/^$/d' <<< \
	$(sed -r '/^ /d' <<< $(sed -r 's/,/ /g' <<< "$rules")))

# Fetch matching packets according to the rules.
output=""
while read -r line; do
    conditions=($(awk '{print $1,$2,$3,$4}' <<< "$line"))
    temp_output="$packets"
    for condition in "${conditions[@]}"; do
        temp_output=$(sort <<< $(echo -n "$temp_output" | ./firewall.exe \
                                                          "$condition"))
    done
    output+="$temp_output""new_line"
done <<< "$rules"

#Filttering repeating packets, and sorting for wanted output format.
output=$(sed -r '/^$/d' <<< $(sort -n -k6 <<< \
	$(sed -r 's/new_line/\n/g' <<< "$output")| uniq))
echo "$output" 
