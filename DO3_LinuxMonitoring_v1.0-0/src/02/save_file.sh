#!/bin/bash

echo -n "Save data to file? (Y/N) "
read -r answer
if [[ $answer = 'Y' || $answer = 'y' ]]; then
  file_name=$(date +"%d_%m_%y_%H_%M_%S.status")
  mv temp "$file_name"
else
  rm temp
fi
