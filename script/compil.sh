#!/bin/sh
gcc -o MediaPlayer mediaplayer/MediaPlayer.c `pkg-config --cflags --libs gtk+-3.0`
gcc -o MonPG1 pg1/MonPG1.c
gcc pg2/MonPG2.c -o MonPG2 -lm
gcc pg3/MonPG3.c -o MonPG3 pg3/pbPlots.c pg3/supportLib.c -lm
gcc pg4/MonPG4.c -o MonPG4
gcc pg5/MonPG5.c -o MonPG5
gcc -o MonPG6 pg6/MonPG6.c `pkg-config --cflags --libs gtk+-3.0`
