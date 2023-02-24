#!/bin/bash

mkdir -p artifacts
cd ./src/$1
make
mv s21_$1 ../../artifacts
cd ../tests
if [[ -f ../../artifacts/s21_$1 ]]; then
  echo "Building $1: SUCCESS  ✅" >> message_build_$1.txt
else
  echo "Building $1: FAIL ❌"  >> message_build_$1.txt
  exit 1
fi
