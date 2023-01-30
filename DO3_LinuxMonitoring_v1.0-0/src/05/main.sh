#!/bin/bash

FILE=./directory_check.sh
if ! [ -f "$FILE" ]; then
    echo "Missing script file: $FILE"
    exit
fi

start_time=$(date +'%s')
chmod +rx directory_check.sh

if [[ $# != 1 ]]; then
    echo "1 parameter required - path to directory ended with '/'"
elif ! [[ -d $1 ]]; then
    echo "There is no such directory"
elif ! [[ $1 =~ .*\/$ ]]; then
    echo "1 parameter required - path to directory ending with '/'"
else
    ./directory_check.sh $1"*"
    end_time=$(date +'%s')
    echo "Script execution time (in seconds) = $(( end_time - start_time ))"
fi
