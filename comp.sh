#!/bin/bash

gcc al.c -o main -L/usr/local/lib -lallegro_image -lallegro_main -lallegro_audio -lallegro_dialog -lallegro_acodec -lallegro -lallegro_primitives -lallegro_font -lallegro_ttf -lallegro

./main
