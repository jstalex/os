#!/bin/bash

while true
do
    if read line; then
        echo $line `date` >> result.txt
    fi
done <"rfid_data"