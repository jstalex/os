#!/bin/bash

./stage-03-01.sh &

pass=""

while true
do
    while read sym && [[ "$sym" != '*' ]]
    do
        pass+="$sym"
        echo "$pass"
    done

    if [[ "$pass" == '1337' ]]; then
        echo "Successful entry" >> result.txt
    fi

    if [[ "$sym" == '*' ]]; then
        pass=""
    fi
done <"keypad_data"