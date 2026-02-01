#!/bin/bash

input_dir="assets/musics"
output_dir="src/songs"

for filepath in "$input_dir"/*.uge; do
  filename=$(basename "$filepath" .uge)
  echo $filepath
  ~/bin/hUGETracker-1.0.11-linux/uge2source \
    "$filepath" \
    -b 255 \
    "$filename" \
    "src/musics/$filename.c"
done
