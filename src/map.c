#include "map.h"
#include "common.h"
#include "log.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdlib.h>

extern Logger* logger;

Map* map_new(SDL_Surface* surface) {
    if (surface->format->BitsPerPixel != 8 && surface->format->BitsPerPixel != 32) {
        logger_log(logger, WARN, "Unsupported BMP format for map:");
        logger_log_i(logger, WARN, surface->format->BitsPerPixel);
        logger_log(logger, WARN, "Will use missing texture pattern instead.");
    }
    Map* map = malloc(sizeof(Map));
    *map = (Map){
        .surface = surface
    };
    return map;
}

Map* map_new_bmp(const char* file) {
    IMG_Init(IMG_INIT_PNG);

    logger_log(logger, INFO, "Creating map from file:");
    logger_log(logger, INFO, file);

    SDL_RWops *rwop = SDL_RWFromFile(file, "rb");
    SDL_Surface* surface = IMG_Load_RW(rwop, 1); // The one here indicates that rwop should be closed automagically
    if (!surface) {
        logger_log(logger, ERROR, "Couldn't load map image file:");
        logger_log(logger, ERROR, "IMG_GetError:");
        logger_log(logger, ERROR, IMG_GetError());
        return NULL;
    }
    IMG_Quit();

    return map_new(surface);
}

SDL_Color map_get_coords(Map* map, int x, int y) {
    x = mod(x, map->surface->w);
    y = mod(y, map->surface->h);

    if (map->surface->format->BitsPerPixel == 32) {
        Uint8* pixel = (Uint8*)map->surface->pixels + y*map->surface->pitch + x*4;
        SDL_Color color = {};
        SDL_GetRGBA(*(Uint32*)pixel, map->surface->format, &color.r, &color.g, &color.b, &color.a);
        return color;
    } else if(map->surface->format->BitsPerPixel == 8) {
        Uint8* pixel = (Uint8*)map->surface->pixels + y*map->surface->pitch + x;
        return map->surface->format->palette->colors[*pixel];
    } else {
        // Missing texture checkerboard
        int square = y%64 < 32 ? x%64 < 32 : x%64 > 32;
        return (SDL_Color){square? 255 : 0, 0, square? 255 : 0, 255};
    }
}

void map_free(Map* map) {
    SDL_FreeSurface(map->surface);
    free(map);
}
