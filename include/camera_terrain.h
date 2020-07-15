#pragma once

#include "entity.h"
#include "map.h"
#include "engine.h"

typedef struct {
    int x, y, z;
    float dir;
    Map* height_map;
    Map* color_map;
} Camera_Terrain_Data;

Entity* camera_terrain_new(Engine* engine, int x, int y, int z, float dir, Map* height_map, Map* color_map);
