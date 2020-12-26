#include "entity.h"
#include "slev_map.h"
#include "camera_terrain.h"
#include "debug_map.h"
#include "log.h"
#include <stdlib.h>

extern Logger* logger;

static void debug_map_draw(void* entity, int dt) {
    Debug_Map_Data* debug_map_data = ((Entity*)entity)->entity_data;
    Engine* engine = ((Entity*)entity)->engine;
    Slev_Map* map = debug_map_data->map;
    for (int x = 0; x < map->w; x+=1) {
        for (int y = 0; y < map->h; y+=1) {
            SDL_Color color = slev_map_get_coords(map, x, y).color;
            int height = slev_map_get_coords(map, x, y).height;
            SDL_SetRenderDrawColor(engine->ren, color.r/2+height/2, color.g/2+height/2, color.b/2+height/2, 255);
            SDL_RenderDrawPoint(engine->ren, x, y);
        }
    }
}

static void debug_map_free(void* entity) {
    Debug_Map_Data* debug_map_data = ((Entity*)entity)->entity_data;
    free(debug_map_data);
    ((Entity*)entity)->entity_data = NULL;
}

Entity* debug_map_new(void* engine, Slev_Map* map, Camera_Terrain_Data* camera_data) {
    Entity* debug_map = entity_new(
        engine,
        ENTTYPE_NONE,
        NULL,
        NULL,
        debug_map_draw,
        debug_map_free
    );

    Debug_Map_Data* debug_map_data = malloc(sizeof(Debug_Map_Data));
    *debug_map_data = (Debug_Map_Data){
        .map = map,
        .camera_data = camera_data
    };

    debug_map->entity_data = debug_map_data;

    return debug_map;
}
