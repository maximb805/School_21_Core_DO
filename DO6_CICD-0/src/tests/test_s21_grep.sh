#!/bin/bash

args=""
counter=0
TEST_DIR="./src/tests"

get_res()
{
  (( counter++ ))
  ./artifacts/s21_grep $args > $TEST_DIR/1.txt 2>$TEST_DIR/1_err.txt
  grep $args > $TEST_DIR/2.txt 2>$TEST_DIR/2_err.txt
  diff $TEST_DIR/1.txt $TEST_DIR/2.txt > $TEST_DIR/3.txt
  ERRORS=$(( $(wc $TEST_DIR/1_err.txt | awk '{printf $1}') - $(wc $TEST_DIR/2_err.txt | awk '{printf $1}') ))
  if [[ -s 3.txt || $ERRORS != 0 ]]; then
    echo "Test $counter: FAIL"
  else
    echo "Test $counter: OK"
  fi
}

args=" -e char $TEST_DIR/test_1_grep.txt"
get_res $args
args=" -f $TEST_DIR/test_2_grep.txt $TEST_DIR/test_3_grep.txt $TEST_DIR/test_1_grep.txt"
get_res $args
args=" -f $TEST_DIR/test_2_grep.txt -e char $TEST_DIR/test_3_grep.txt"
get_res $args
args=" -f ./not_exists.txt -e char $TEST_DIR/test_3_grep.txt"
get_res $args

for arg in c h i l n o s v
do
  for file in $TEST_DIR/test_3_grep.txt $TEST_DIR/test_4_grep.txt ./not_exists.txt
  do
    args=" -e in -$arg $file $TEST_DIR/test_1_grep.txt"
    get_res "$args"
  done
done

for arg in c h i l n o s v
do
  for arg2 in c h i l n o s v
  do
    if [[ $arg < $arg2 ]]; then
      args=" -e in -$arg -$arg2 $TEST_DIR/test_3_grep.txt $TEST_DIR/test_1_grep.txt"
      get_res "$args"
    fi
  done
done

cd $TEST_DIR || exit
rm 1.txt 2.txt 3.txt 1_err.txt 2_err.txt
