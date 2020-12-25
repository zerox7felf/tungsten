CC=gcc
INCLUDE_DIR=include
SRC_DIR=src
BUILD_DIR=bin
FLAGS=-I$(INCLUDE_DIR) -Wall `sdl-config --cflags` -lSDL2 -lm -lSDL2_ttf  -lSDL2_image

OBJS=log

all: $(BUILD_DIR)/tungsten

slev: $(BUILD_DIR)/slev

$(BUILD_DIR)/common.o: $(INCLUDE_DIR)/common.h $(SRC_DIR)/common.c
	$(CC) -c $(SRC_DIR)/common.c $(FLAGS) -o $(BUILD_DIR)/common.o

$(BUILD_DIR)/camera_terrain.o: $(INCLUDE_DIR)/camera_terrain.h $(SRC_DIR)/camera_terrain.c
	$(CC) -c $(SRC_DIR)/camera_terrain.c $(FLAGS) -o $(BUILD_DIR)/camera_terrain.o

$(BUILD_DIR)/debug_map.o: $(INCLUDE_DIR)/debug_map.h $(SRC_DIR)/debug_map.c
	$(CC) -c $(SRC_DIR)/debug_map.c $(FLAGS) -o $(BUILD_DIR)/debug_map.o

$(BUILD_DIR)/map.o: $(INCLUDE_DIR)/map.h $(SRC_DIR)/map.c
	$(CC) -c $(SRC_DIR)/map.c $(FLAGS) -o $(BUILD_DIR)/map.o

$(BUILD_DIR)/player.o: $(INCLUDE_DIR)/player.h $(SRC_DIR)/player.c
	$(CC) -c $(SRC_DIR)/player.c $(FLAGS) -o $(BUILD_DIR)/player.o

$(BUILD_DIR)/entity.o: $(INCLUDE_DIR)/entity.h $(SRC_DIR)/entity.c
	$(CC) -c $(SRC_DIR)/entity.c $(FLAGS) -o $(BUILD_DIR)/entity.o

$(BUILD_DIR)/engine.o: $(INCLUDE_DIR)/engine.h $(SRC_DIR)/engine.c
	$(CC) -c $(SRC_DIR)/engine.c $(FLAGS) -o $(BUILD_DIR)/engine.o

$(BUILD_DIR)/log.o: $(INCLUDE_DIR)/log.h $(SRC_DIR)/log.c
	$(CC) -c $(SRC_DIR)/log.c $(FLAGS) -o $(BUILD_DIR)/log.o

$(BUILD_DIR)/tungsten: $(SRC_DIR)/main.c $(BUILD_DIR)/log.o $(BUILD_DIR)/engine.o $(BUILD_DIR)/entity.o $(BUILD_DIR)/player.o $(BUILD_DIR)/map.o $(BUILD_DIR)/debug_map.o $(BUILD_DIR)/camera_terrain.o $(BUILD_DIR)/common.o
	$(CC) $(SRC_DIR)/main.c $(BUILD_DIR)/log.o $(BUILD_DIR)/engine.o $(BUILD_DIR)/entity.o $(BUILD_DIR)/player.o $(BUILD_DIR)/map.o $(BUILD_DIR)/camera_terrain.o $(BUILD_DIR)/debug_map.o $(BUILD_DIR)/common.o $(FLAGS) -o $(BUILD_DIR)/tungsten

$(BUILD_DIR)/slev: $(SRC_DIR)/slev.c $(BUILD_DIR)/log.o $(BUILD_DIR)/map.o $(BUILD_DIR)/common.o
	$(CC) $(SRC_DIR)/slev.c $(BUILD_DIR)/log.o $(BUILD_DIR)/map.o $(BUILD_DIR)/common.o $(FLAGS) -o $(BUILD_DIR)/slev

.PHONY: run clean

run: all
	$(BUILD_DIR)/tungsten

debug: FLAGS += -g
debug: clean all

clean:
	rm $(BUILD_DIR)/*
