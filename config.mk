CC=gcc
INCLUDE_DIR=include
SRC_DIR=src
BUILD_DIR=bin
FLAGS=-I$(INCLUDE_DIR) -Wall `sdl-config --cflags` -lSDL2 -lm -lSDL2_ttf  -lSDL2_image
