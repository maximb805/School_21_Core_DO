#!/bin/bash

FILE=./colours.conf
def_back_1=6
def_font_1=1
def_back_2=2
def_font_2=4
is_back_1_def=0
is_font_1_def=0
is_back_2_def=0
is_font_2_def=0

if ! [ -f "$FILE" ]; then
    echo "File colours.conf missing! Default colour scheme will be used"
    column1_background=$def_back_1
    column1_font_color=$def_font_1
    column2_background=$def_back_2
    column2_font_color=$def_font_2
    is_back_1_def=1
    is_font_1_def=1
    is_back_2_def=1
    is_font_2_def=1
else
    . colours.conf
    if [ -z $column1_background ]; then
        is_back_1_def=1
        column1_background=$def_back_1
    elif [[ $column1_background != [1-6] ]]; then
        echo "Parameters must be numbers between 1 and 6"
        exit
    fi
    if [ -z $column1_font_color ]; then
        is_font_1_def=1
        column1_font_color=$def_font_1
    elif [[ $column1_font_color != [1-6] ]]; then
        echo "Parameters must be numbers between 1 and 6"
        exit
    fi
    if [ -z $column2_background ]; then
        is_back_2_def=1
        column2_background=$def_back_2
    elif [[ $column2_background != [1-6] ]]; then
        echo "Parameters must be numbers between 1 and 6"
        exit
    fi
    if [ -z $column2_font_color ]; then
        is_font_2_def=1
        column2_font_color=$def_font_2
    elif [[ $column2_font_color != [1-6] ]]; then
        echo "Parameters must be numbers between 1 and 6"
        exit
    fi
fi

if [[ $is_back_1_def -eq 1 || $is_font_1_def -eq 1 ]]; then
    if [[ $column1_background -eq $column1_font_color ]]; then
        if [[ $column1_background -eq $def_font_1 ]]; then
            column1_font_color=$def_back_1
        else
            column1_background=$def_font_1
        fi
    fi
fi

if [[ $is_back_2_def -eq 1 || $is_font_2_def -eq 1 ]]; then
    if [[ $column2_background -eq $column2_font_color ]]; then
        if [[ $column2_background -eq $def_font_2 ]]; then
            column2_font_color=$def_back_2
        else
            column2_background=$def_font_2
        fi
    fi
fi
