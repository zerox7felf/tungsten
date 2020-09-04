#pragma once

#include "entity.h"
#include "camera_terrain.h"
#include "map.h"
#include <SDL2/SDL.h>

typedef struct {
    Map* map;
    Camera_Terrain_Data* camera_data;
} Debug_Map_Data;

Entity* debug_map_new(void* engine, Map* map, Camera_Terrain_Data* camera_data);
