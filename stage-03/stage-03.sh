#!/bin/bash

# it will be initial script, rfid reader and keypad will be launching here

# sudo ./keypad_v8_asp -q keypad_data &
# pid1=$!
# sudo ./rfid_reader_asp -q rfid_data &
# pid2=$!

./stage-03-01.sh &
pid3=$!

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

kill $pid1 $pid2 $pid3