#!/bin/bash

TEST_DIR="./src/tests"

cat $TEST_DIR/result.txt
ERRORS=$(grep FAIL $TEST_DIR/result.txt | wc | awk '{print $1}')
if [[ ERRORS -gt 0 ]]; then
  echo "Functional test: FAIL"
  echo "Test $1: FAIL ❌" >> $TEST_DIR/message_test_$1.txt
  exit 1
else
  echo "Functional test : SUCCESS"
  echo "Test $1: SUCCESS  ✅" >> $TEST_DIR/message_test_$1.txt
fi
