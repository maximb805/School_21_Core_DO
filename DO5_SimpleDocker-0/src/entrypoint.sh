#!/bin/bash

gcc -Wall -Werror -Wextra /home/server.c -o /home/server -lfcgi
spawn-fcgi /home/server -p 8080
nginx -g "daemon off;"
