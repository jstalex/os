#!/bin/bash

./stage-03-01.sh &
pid=$!

pass=""
flag=1

# kill scrtipts by send # in keypad_data

while [[ flag == 1 ]]
do
    while read sym && [[ "$sym" != '*' ]]
    do
        pass+="$sym"
        echo "$pass"
    done

    if [[ "$pass" == '1337' ]]; then
        echo "Successful entry" >> result.txt
    fi

    if [[ "$pass" == '#' ]]; then
        flag=0
    fi

    if [[ "$sym" == '*' ]]; then
        pass=""
    fi
done <"keypad_data"

kill $pid