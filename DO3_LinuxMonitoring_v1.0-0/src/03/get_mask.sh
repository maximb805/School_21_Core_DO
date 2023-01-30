#!/bin/bash

mask=$(ip a | grep "inet " | grep -v " lo" | sed -n '1'p | sed -r 's/.+\/([0-9]{1,2}).+/\1/')
mask_str=""
last_num=0
for_div=0

for (( i = 4; i > 0; i-- )); do
    for_div=256
    last_num=0
    for (( j = 8; j > 0; j-- )); do
      if [[ $mask -gt 0 ]]; then
          (( for_div = for_div / 2 ))
          (( last_num= last_num + for_div ))
          (( mask-- ))
      else
          j=0
      fi
    done
    mask_str=$mask_str"$last_num"
    if [[ i -gt 1 ]]; then
        mask_str=$mask_str"."
    fi
done

echo "$mask_str"
