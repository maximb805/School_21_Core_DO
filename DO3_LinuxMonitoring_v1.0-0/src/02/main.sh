#!/bin/bash

FILE=./get_mask.sh
if ! [ -f "$FILE" ]; then
    echo "Missing script file: $FILE"
    exit
fi
FILE=./save_file.sh
if ! [ -f "$FILE" ]; then
    echo "Missing script file: $FILE"
    exit
fi

chmod +rx get_mask.sh save_file.sh
{
  echo "HOSTNAME = $(hostname)"
  echo "TIMEZONE = $(timedatectl | grep "Time zone" | sed 's/.*Time zone: //')"
  echo "USER = $(whoami)"
  echo "OS = $(hostnamectl | grep "Operating System" | sed 's/.*Operating System: //')"
  echo "DATE = $(date +"%d %b %Y %H:%M:%S")"
  echo "UPTIME = $(uptime -p)"
  echo "UPTIME_SEC = $(awk '{print $1}' /proc/uptime)"
  echo "IP = $(ip a | grep "inet " | grep -v " lo" | sed -n '1'p | sed -r 's/\/.+//' | awk '{print $2}')"
  echo "MASK = $(./get_mask.sh)"
  echo "GATEWAY = $(ip r | grep "default via" | awk '{print $3}')"
  echo "RAM_TOTAL = $(free | grep Mem | awk '{printf "%.3f Gb", $2 / 1048576}')"
  echo "RAM_USED = $(free | grep Mem | awk '{printf "%.3f Gb", $3 / 1048576}')"
  echo "RAM_FREE = $(free | grep Mem | awk '{printf "%.3f Gb", $4 / 1048576}')"
  echo "SPACE_ROOT = $(df |grep "/$" | awk '{printf "%.2f Gb", $2 / 1048576}')"
  echo "SPACE_ROOT_USED = $(df | grep "/$" | awk '{printf "%.2f Gb", $3 / 1048576}')"
  echo "SPACE_ROOT_FREE = $(df | grep "/$" | awk '{printf "%.2f Gb", $4 / 1048576}')"
} > temp
cat temp
./save_file.sh
