#!/bin/bash

# it will be initial script, rfid reader and keypad will be launching here

sudo ./keypad_v8_asp -q keypad_data &
pid1=$!
sudo ./rfid_reader_asp -q rfid_data &
pid2=$!

./combiner $pid1 $pid2