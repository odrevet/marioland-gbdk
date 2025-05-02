#!/bin/bash

input_dir="assets/sounds"
output_dir="src/sounds"

for filepath in "$input_dir"/*.vgm; do
  filename=$(basename "$filepath" .vgm)
  python ~/projects/VGM2GBSFX/utils/vgm2data.py \
    -o "$output_dir/$filename.c" \
    -i "$filename" \
    "$filepath"
done
