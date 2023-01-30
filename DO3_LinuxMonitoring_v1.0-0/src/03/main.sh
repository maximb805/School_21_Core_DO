#!/bin/bash

FILE=./get_data.sh
if ! [ -f "$FILE" ]; then
    echo "Missing script file: $FILE"
    exit
fi
FILE=./get_mask.sh
if ! [ -f "$FILE" ]; then
    echo "Missing script file: $FILE"
    exit
fi
FILE=./colourize.sh
if ! [ -f "$FILE" ]; then
    echo "Missing script file: $FILE"
    exit
fi

if ! [[ $# -eq 4 ]]; then
  echo "4 parameters required"
  exit
fi

for param in "$@"
do
  if ! [[ $param =~ ^[0-9]+$ ]]; then
    echo "Parameters must be numbers between 1 and 6"
    exit
  elif [[ $param -gt 6 || $param -lt 1 ]]; then
    echo "Parameters must be numbers between 1 and 6"
    exit
  fi
done

if [[ $1 -eq $2 || $3 -eq $4 ]]; then
  echo "Pairs of numbers means column background colour and column text colour, so they can't be equal"
  exit
fi

chmod +rx get_data.sh get_mask.sh colourize.sh
./colourize.sh "$1" "$2" "$3" "$4"
