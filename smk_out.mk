include config.mk
$(BUILD_DIR)/map.o: $(SRC_DIR)/map.c $(INCLUDE_DIR)/map.h 
	$(CC) -c $(SRC_DIR)/map.c $(FLAGS) -o $(BUILD_DIR)/map.o
$(BUILD_DIR)/slev_map.o: $(SRC_DIR)/slev_map.c $(INCLUDE_DIR)/slev_map.h 
	$(CC) -c $(SRC_DIR)/slev_map.c $(FLAGS) -o $(BUILD_DIR)/slev_map.o
$(BUILD_DIR)/camera_terrain.o: $(SRC_DIR)/camera_terrain.c $(INCLUDE_DIR)/camera_terrain.h 
	$(CC) -c $(SRC_DIR)/camera_terrain.c $(FLAGS) -o $(BUILD_DIR)/camera_terrain.o
$(BUILD_DIR)/player.o: $(SRC_DIR)/player.c $(INCLUDE_DIR)/player.h 
	$(CC) -c $(SRC_DIR)/player.c $(FLAGS) -o $(BUILD_DIR)/player.o
$(BUILD_DIR)/debug_map.o: $(SRC_DIR)/debug_map.c $(INCLUDE_DIR)/debug_map.h 
	$(CC) -c $(SRC_DIR)/debug_map.c $(FLAGS) -o $(BUILD_DIR)/debug_map.o
$(BUILD_DIR)/common.o: $(SRC_DIR)/common.c $(INCLUDE_DIR)/common.h 
	$(CC) -c $(SRC_DIR)/common.c $(FLAGS) -o $(BUILD_DIR)/common.o
$(BUILD_DIR)/controller.o: $(SRC_DIR)/controller.c $(INCLUDE_DIR)/controller.h 
	$(CC) -c $(SRC_DIR)/controller.c $(FLAGS) -o $(BUILD_DIR)/controller.o
$(BUILD_DIR)/entity.o: $(SRC_DIR)/entity.c $(INCLUDE_DIR)/entity.h 
	$(CC) -c $(SRC_DIR)/entity.c $(FLAGS) -o $(BUILD_DIR)/entity.o
$(BUILD_DIR)/engine.o: $(SRC_DIR)/engine.c $(INCLUDE_DIR)/engine.h 
	$(CC) -c $(SRC_DIR)/engine.c $(FLAGS) -o $(BUILD_DIR)/engine.o
$(BUILD_DIR)/log.o: $(SRC_DIR)/log.c $(INCLUDE_DIR)/log.h 
	$(CC) -c $(SRC_DIR)/log.c $(FLAGS) -o $(BUILD_DIR)/log.o
$(BUILD_DIR)/slev: $(SRC_DIR)/slev.c $(BUILD_DIR)/log.o $(BUILD_DIR)/map.o $(BUILD_DIR)/common.o $(BUILD_DIR)/slev_map.o 
	$(CC) $(SRC_DIR)/slev.c $(BUILD_DIR)/log.o $(BUILD_DIR)/map.o $(BUILD_DIR)/common.o $(BUILD_DIR)/slev_map.o $(FLAGS) -o $(BUILD_DIR)/slev
$(BUILD_DIR)/tungsten: $(SRC_DIR)/main.c $(BUILD_DIR)/common.o $(BUILD_DIR)/camera_terrain.o $(BUILD_DIR)/debug_map.o $(BUILD_DIR)/map.o $(BUILD_DIR)/player.o $(BUILD_DIR)/entity.o $(BUILD_DIR)/engine.o $(BUILD_DIR)/log.o $(BUILD_DIR)/controller.o $(BUILD_DIR)/slev_map.o 
	$(CC) $(SRC_DIR)/main.c $(BUILD_DIR)/common.o $(BUILD_DIR)/camera_terrain.o $(BUILD_DIR)/debug_map.o $(BUILD_DIR)/map.o $(BUILD_DIR)/player.o $(BUILD_DIR)/entity.o $(BUILD_DIR)/engine.o $(BUILD_DIR)/log.o $(BUILD_DIR)/controller.o $(BUILD_DIR)/slev_map.o $(FLAGS) -o $(BUILD_DIR)/tungsten
