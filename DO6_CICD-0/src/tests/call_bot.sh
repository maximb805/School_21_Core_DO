#!/bin/bash

TEST_DIR=./src/tests
chmod +x $TEST_DIR/bot_notifications.sh
if [[ $CI_JOB_STATUS == failed ]]; then
  echo "Deploy status: FAIL ❌" > $TEST_DIR/message.txt
  $TEST_DIR/bot_notifications.sh $TEST_DIR/message.txt
else
  echo "Deploy status: SUCCESS ✅" > $TEST_DIR/message.txt
  $TEST_DIR/bot_notifications.sh $TEST_DIR/message.txt
fi
