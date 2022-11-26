#!/bin/bash

fifo_name="rfid_data"

while true
do
    if read line; then
        echo $line `date` > result.txt
    fi
done <"$fifo_name"  