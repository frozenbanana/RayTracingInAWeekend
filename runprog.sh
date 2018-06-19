#!/bin/bash
g++ main.cpp -o run
./run >> output.ppm
xdg-open output.ppm
