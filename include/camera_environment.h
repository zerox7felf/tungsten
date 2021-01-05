#pragma once

#include "entity.h"
#include "map.h"
#include "slev_map.h"

typedef struct {
    Entity* camera_terrain;
    Map* z_buffer;
    float x, y, z;
    float dir, dir_vert;
    Slev_Map* map;
} Camera_Environment_Data;

Entity* camera_environment_new(Engine* engine, int x, int y, int z, float dir, Slev_Map* map);
