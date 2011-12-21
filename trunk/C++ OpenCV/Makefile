#!/usr/bin/make
# Makefile for opencv compilation
CC=g++
OPENCV=-I/usr/local/include/opencv -L/usr/local/lib -lcxcore -lcv -lhighgui 

all: clean mandelbrot julia

mandelbrot:
	$(CC) mandelbrot.cpp -o mandelbrot $(OPENCV)

julia:
	$(CC) julia.cpp -o julia $(OPENCV)

clean:
	rm -rf *o mandelbrot julia

