#pragma once

#include "entity.h"
#include "map.h"
#include "slev_map.h"
#include "engine.h"

typedef struct {
    float x, y, z;
    float dir, dir_vert;
    Map* height_map;
    Map* height_map_lod;
    Map* color_map;
    Map* color_map_lod;
    Slev_Map* map;
} Camera_Terrain_Data;

//Entity* camera_terrain_new(Engine* engine, int x, int y, int z, float dir, Map* height_map, Map* color_map);
Entity* camera_terrain_new(Engine* engine, int x, int y, int z, float dir, Slev_Map* map);
