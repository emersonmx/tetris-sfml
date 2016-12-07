#!/bin/bash

inkscape src/block.svg --export-png=block.png
inkscape src/grid.svg --export-png=grid.png
lame src/main_music.wav main_music.mp3
