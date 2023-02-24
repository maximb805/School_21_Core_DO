#!/bin/bash

cd ./src/$1
cp ../../materials/linters/.clang-format .
clang-format -n *.c *.h 2>./style_test.txt
cat ./style_test.txt
if [[ -s ./style_test.txt ]]; then
  echo "Code style $1: FAIL ❌" >> ./../tests/message_style_$1.txt
  exit 1
fi
echo "Code style $1: SUCCESS  ✅" >> ./../tests/message_style_$1.txt
