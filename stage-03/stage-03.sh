#!/bin/bash

fifo_name="rfid_data"

while true
do
    if read line; then
        echo $line
    fi
done <"$fifo_name"