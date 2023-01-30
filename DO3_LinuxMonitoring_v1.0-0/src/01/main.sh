#!/bin/bash

reg_exp='^[-+]?[0-9]+(\.[0-9]+)?$'

if [ $# -eq 1 ]; then
  if ! [[ $1 =~ $reg_exp ]]; then
    echo "$1"
  else
    echo "Argument can't be a number!"
  fi
elif [ $# -gt 1 ]; then
  echo "Too much arguments, only 1 required"
else
  echo "Argument required"
fi
