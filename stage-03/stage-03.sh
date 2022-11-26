#!/bin/bash

while true
do
    if read line <"rfid_data"; then
        echo $line `date` >> result.txt
    fi
    if read pass <"keypad_data" && [[ "$pass" == '1337' ]]; then
        echo "Successful entry" >> result.txt
    fi
done 