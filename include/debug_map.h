#pragma once

#include "entity.h"
#include "camera_terrain.h"
#include "slev_map.h"
#include <SDL2/SDL.h>

typedef struct {
    Slev_Map* map;
    Camera_Terrain_Data* camera_data;
} Debug_Map_Data;

Entity* debug_map_new(void* engine, Slev_Map* map, Camera_Terrain_Data* camera_data);
