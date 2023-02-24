#!/bin/bash

TEST_DIR=./src/tests
if [[ -f $TEST_DIR/message_build_cat.txt ]]; then
  cat $TEST_DIR/message_build_cat.txt >> $TEST_DIR/message.txt 2>/dev/null
fi
if [[ -f $TEST_DIR/message_build_grep.txt ]]; then
  cat $TEST_DIR/message_build_grep.txt >> $TEST_DIR/message.txt 2>/dev/null
fi
if [[ -f $TEST_DIR/message_style_cat.txt ]]; then
  cat $TEST_DIR/message_style_cat.txt >> $TEST_DIR/message.txt 2>/dev/null
fi
if [[ -f $TEST_DIR/message_style_grep.txt ]]; then
  cat $TEST_DIR/message_style_grep.txt >> $TEST_DIR/message.txt 2>/dev/null
fi
if [[ -f $TEST_DIR/message_test_cat.txt ]]; then
  cat $TEST_DIR/message_test_cat.txt >> $TEST_DIR/message.txt 2>/dev/null
fi
if [[ -f $TEST_DIR/message_test_grep.txt ]]; then
  cat $TEST_DIR/message_test_grep.txt >> $TEST_DIR/message.txt 2>/dev/null
fi
