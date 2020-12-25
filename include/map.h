#pragma once

#include <SDL2/SDL.h>

//  Map used for color and heightmaps

typedef struct {
    SDL_Surface* surface;
} Map;

Map* map_new(SDL_Surface* surface);
Map* map_new_bmp(const char* file);
SDL_Color map_get_coords(Map* map, int x, int y);
void map_free(Map* map);
