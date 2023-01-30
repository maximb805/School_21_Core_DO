#!/bin/bash

echo -n "Total number of folders (including all nested ones) = "
    find $1 -type d 2>/dev/null  | wc -l

echo "TOP 5 folders of maximum size arranged in descending order (path and size):"
    find $1 -type d -exec du -h {} + 2>/dev/null | sort -hr | head -n 5 | awk '{print NR, "-", $2"/, "$1}'

echo -n "Total number of files = "
    find $1 -type f  2>/dev/null | wc -l

echo "Number of:"
    echo -n "Configuration files (with the .conf extension) = "
        find $1 -type f 2>/dev/null | grep -c ".*\.conf$"
    echo -n "Text files = "
        find $1 -type f 2>/dev/null | grep -c ".*\.txt$"
    echo -n "Executable files = "
        find $1 -type f -executable 2>/dev/null | wc -l
    echo -n "Log files (with the extension .log) = "
        find $1 -type f 2>/dev/null | grep -c ".*\.log$"
    echo -n "Archive files = "
        find $1 -type f -iname "*.7z" -or -iname "*.gz" -or -iname "*.gzip" \
            -or -iname "*.jar" -or -iname "*.pak" -or -iname "*.pkg" -or -iname "*.rar" \
            -or -iname "*.tar" -or -iname "*.tar-gz" -or -iname "*.tgz" -or -iname "*.war" \
            -or -iname "*.zip" -or -iname "*.zipx" 2>/dev/null | wc -l
    echo -n "Symbolic links = "
        find $1 -type l 2>/dev/null | wc -l

echo "TOP 10 files of maximum size arranged in descending order (path, size and type):"
    find $1 -type f -exec du -ha {} + 2>/dev/null| grep -v "s21_temp" | sort -hr | head -n 10 | awk '{print NR" - "$2", "$1}' > s21_temp
    lines=$(wc -l "s21_temp" | awk '{print$1}')
    for (( i = 1; i <= lines; i++ )); do
        type=$(sed -n "$i"p s21_temp | awk '{print$3}' | sed -r 's/.*\.(.+),$/\1/')
        if ! [[ $type =~ .*,$ ]]; then
            echo "$(sed -n "$i"p s21_temp)"", $type"
        else
            sed -n "$i"p s21_temp
        fi
    done
    rm s21_temp

echo "TOP 10 executable files of the maximum size arranged in descending order (path, size and MD5 hash of file):"
    find $1 -type f -executable -exec du -ha {} + 2>/dev/null| grep -v "s21_temp" | sort -hr | head -n 10 | awk '{print NR" - "$2", "$1}' > s21_temp
    lines=$(wc -l "s21_temp" | awk '{print$1}')
    for (( i = 1; i <= lines; i++ )); do
        path=$(sed -n "$i"p s21_temp | awk '{print$3}' | sed  's/,$//')
        hash=$(md5sum "$path" | awk '{print$1}')
        echo "$(sed -n "$i"p s21_temp)"", $hash"
    done
    rm s21_temp
