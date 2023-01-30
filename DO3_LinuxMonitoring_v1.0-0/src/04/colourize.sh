#!/bin/bash

TEXT_WHITE='\033[37m'
TEXT_RED='\033[31m'
TEXT_GREEN='\033[32m'
TEXT_BLUE='\033[34m'
TEXT_PURPLE='\033[35m'
TEXT_BLACK='\033[30m'

BACK_WHITE='\033[47m'
BACK_RED='\033[41m'
BACK_GREEN='\033[42m'
BACK_BLUE='\033[44m'
BACK_PURPLE='\033[45m'
BACK_BLACK='\033[40m'

DEFAULT='\033[0m'

odd_check=1
param_num=1
back_1=""
text_1=""
back_2=""
text_2=""
param=""

for params in "$@"
do
    if [[ $odd_check -lt 0 ]]; then
        case $params in
            1)param="${TEXT_WHITE}";;
            2)param="${TEXT_RED}";;
            3)param="${TEXT_GREEN}";;
            4)param="${TEXT_BLUE}";;
            5)param="${TEXT_PURPLE}";;
            6)param="${TEXT_BLACK}";;
        esac
    else
        case $params in
            1)param="${BACK_WHITE}";;
            2)param="${BACK_RED}";;
            3)param="${BACK_GREEN}";;
            4)param="${BACK_BLUE}";;
            5)param="${BACK_PURPLE}";;
            6)param="${BACK_BLACK}";;
        esac
    fi
    case $param_num in
        1)back_1=$param;;
        2)text_1=$param;;
        3)back_2=$param;;
        4)text_2=$param;;
    esac
    (( param_num++ ))
    (( odd_check = odd_check * (-1) ))
done

./get_data.sh "$back_1" "$text_1" "$back_2" "$text_2" "$DEFAULT"
