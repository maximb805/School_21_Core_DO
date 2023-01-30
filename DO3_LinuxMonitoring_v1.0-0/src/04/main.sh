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
FILE=./set_colour_data.sh
if ! [ -f "$FILE" ]; then
    echo "Missing script file: $FILE"
    exit
fi

chmod +rx get_data.sh get_mask.sh colourize.sh set_colour_data.sh

col1_back=""
col1_font=""
col2_back=""
col2_font=""
result=""
counter=1

. ./set_colour_data.sh

if [[ $column1_background -eq $column1_font_color || $column2_background -eq $column2_font_color ]]; then
    echo "Colours in one column can't be equal"
else
    ./colourize.sh "$column1_background" "$column1_font_color" "$column2_background" "$column2_font_color"

    for colour in $column1_background $column1_font_color $column2_background $column2_font_color
    do
        case $colour in
            1)result="(white)";;
            2)result="(red)";;
            3)result="(green)";;
            4)result="(blue)";;
            5)result="(purple)";;
            6)result="(black)";;
        esac
        case $counter in
            1)col1_back=$result;;
            2)col1_font=$result;;
            3)col2_back=$result;;
            4)col2_font=$result;;
        esac
        (( counter++ ))
    done

    if [[ $is_back_1_def -eq 1 ]]; then
        col1_back="default $col1_back"
    else
        col1_back="$column1_background $col1_back"
    fi
    if [[ $is_font_1_def -eq 1 ]]; then
        col1_font="default $col1_font"
    else
        col1_font="$column1_font_color $col1_font"
    fi
    if [[ $is_back_2_def -eq 1 ]]; then
        col2_back="default $col2_back"
    else
        col2_back="$column2_background $col2_back"
    fi
    if [[ $is_font_2_def -eq 1 ]]; then
        col2_font="default $col2_font"
    else
        col2_font="$column2_font_color $col2_font"
    fi

    echo
    echo "Column 1 background = $col1_back"
    echo "Column 1 font color = $col1_font"
    echo "Column 2 background = $col2_back"
    echo "Column 2 font color = $col2_font"
fi
