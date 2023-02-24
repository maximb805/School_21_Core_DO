#!/bin/bash

scp $(pwd)/artifacts/* gonzalol@192.168.1.105:/usr/local/bin
ssh gonzalol@192.168.1.105 ls /usr/local/bin
