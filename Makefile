CC=gcc
INCLUDE_DIR=include
SRC_DIR=src
BUILD_DIR=bin
FLAGS=-I$(INCLUDE_DIR) -Wall -lSDL2 -lm

OBJS=log

all: $(BUILD_DIR)/tungsten

$(BUILD_DIR)/player.o: $(INCLUDE_DIR)/player.h $(SRC_DIR)/player.c
	$(CC) -c $(SRC_DIR)/player.c $(FLAGS) -o $(BUILD_DIR)/player.o

$(BUILD_DIR)/entity.o: $(INCLUDE_DIR)/entity.h $(SRC_DIR)/entity.c
	$(CC) -c $(SRC_DIR)/entity.c $(FLAGS) -o $(BUILD_DIR)/entity.o

$(BUILD_DIR)/engine.o: $(INCLUDE_DIR)/engine.h $(SRC_DIR)/engine.c
	$(CC) -c $(SRC_DIR)/engine.c $(FLAGS) -o $(BUILD_DIR)/engine.o

$(BUILD_DIR)/log.o: $(INCLUDE_DIR)/log.h $(SRC_DIR)/log.c
	$(CC) -c $(SRC_DIR)/log.c $(FLAGS) -o $(BUILD_DIR)/log.o

$(BUILD_DIR)/tungsten: $(SRC_DIR)/main.c $(BUILD_DIR)/log.o $(BUILD_DIR)/engine.o $(BUILD_DIR)/entity.o $(BUILD_DIR)/player.o
	$(CC) $(SRC_DIR)/main.c $(BUILD_DIR)/log.o $(BUILD_DIR)/engine.o $(BUILD_DIR)/entity.o  $(BUILD_DIR)/player.o $(FLAGS) -o $(BUILD_DIR)/tungsten

.PHONY: run clean

run: all
	$(BUILD_DIR)/tungsten

debug: FLAGS += -g
debug: clean all

clean:
	rm $(BUILD_DIR)/*
