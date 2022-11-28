#!/bin/bash

./stage-03-01.sh &

while true
do
    if read pass && [[ "$pass" == '1337' ]]; then
        echo "Successful entry" >> result.txt
    fi
done <"keypad_data"