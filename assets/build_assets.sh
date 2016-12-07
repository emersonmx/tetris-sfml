#!/bin/bash

inkscape src/block.svg --export-png=block.png
inkscape src/grid.svg --export-png=grid.png

lame src/main_music.wav main_music.mp3

normal_files=$(find src/ -iname "*.wav" ! -name "main_music.wav")

for f in $normal_files
do
    echo "Copying '$f' to current path"
    cp -f $f .
done
