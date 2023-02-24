#!/bin/bash

counter=0
TEST_DIR="./src/tests"

get_res()
{
  (( counter++ ))
  ./artifacts/s21_cat $args > $TEST_DIR/1.txt 2>$TEST_DIR/1_err.txt
  cat $args > $TEST_DIR/2.txt 2>$TEST_DIR/2_err.txt
  diff $TEST_DIR/1.txt $TEST_DIR/2.txt > $TEST_DIR/3.txt
  ERRORS=$(( $(wc $TEST_DIR/1_err.txt | awk '{printf $1}') - $(wc $TEST_DIR/2_err.txt | awk '{printf $1}') ))
  if [[ -s 3.txt || $ERRORS != 0 ]]; then
    echo "Test $counter: FAIL"
  else
    echo "Test $counter: OK"
  fi
}

for arg in n b e v s t T E
do
  for file in $TEST_DIR/test_1_cat.txt $TEST_DIR/test_2_cat.txt ./not_exists.txt
  do
    args="-$arg $file"
    get_res "$args"
  done
done

for arg in E T b e n s t v
do
  for arg2 in E T b e n s t v
  do
    if [[ $arg < $arg2 ]]; then
      args="-$arg -$arg2 $TEST_DIR/test_1_cat.txt"
      get_res "$args"
    fi
  done
done

cd $TEST_DIR || exit
rm 1.txt 2.txt 3.txt 1_err.txt 2_err.txt
