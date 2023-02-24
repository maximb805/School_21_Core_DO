#!/bin/bash

TEST_DIR=./src/tests
chmod +x $TEST_DIR/create_message.sh
chmod +x $TEST_DIR/bot_notifications.sh
$TEST_DIR/create_message.sh
$TEST_DIR/bot_notifications.sh $TEST_DIR/message.txt
rm $TEST_DIR/message*
