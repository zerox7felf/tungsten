#include "map.h"
#include "camera_terrain.h"
#include "entity.h"
#include "engine.h"
#include "log.h"
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>

extern Logger* logger;

static void camera_terrain_init(void* entity) {
}

static void camera_terrain_update(void* entity, int dt) {
    Camera_Terrain_Data* camera_data = (Camera_Terrain_Data*)((Entity*)entity)->entity_data;
    Engine* engine = ((Entity*)entity)->engine;
    if (engine->keyboard_state[SDL_SCANCODE_W])
        camera_data->y--;
    if (engine->keyboard_state[SDL_SCANCODE_S])
        camera_data->y++;
    if (engine->keyboard_state[SDL_SCANCODE_D])
        camera_data->x++;
    if (engine->keyboard_state[SDL_SCANCODE_A])
        camera_data->x--;
    if (engine->keyboard_state[SDL_SCANCODE_LEFT])
        camera_data->dir+=.1;
    if (engine->keyboard_state[SDL_SCANCODE_RIGHT])
        camera_data->dir-=.1;
    if (engine->keyboard_state[SDL_SCANCODE_LSHIFT])
        camera_data->z++;
    if (engine->keyboard_state[SDL_SCANCODE_LCTRL])
        camera_data->z--;
    camera_data->dir = fmodf(camera_data->dir, 2*3.1415f);
}

static void camera_terrain_draw(void* entity, int dt) {
    Camera_Terrain_Data* camera_data = (Camera_Terrain_Data*)((Entity*)entity)->entity_data;
    Engine* engine = (Engine*)((Entity*)entity)->engine;

    int w = 800;
    int h = 600;
    //SDL_GetRendererOutputSize(engine->ren, &w, &h);
    float sindir = sinf(camera_data->dir);
    float cosdir = cosf(camera_data->dir);

    int y_buffer[w];
    //memset(y_buffer, h, w*sizeof(int)); // Initialize variably-sized array the c-way.
    for (int i = 0; i < w; i++)
        y_buffer[i] = h;

    #define HORIZON 120
    #define SCALE_HEIGHT 200.0
    #define DISTANCE 200
    //for (int d = DISTANCE; d > 0; d--) {    // distance to the line in front of the camera, from back to front
    float dd = 1.0; // delta-d
    for (float d = 1.0; d < DISTANCE; d+=dd) {

        // line on map
        float pleft_x = (-cosdir*d - sindir*d) + camera_data->x;
        float pleft_y = ( sindir*d - cosdir*d) + camera_data->y;

        float pright_x = ( cosdir*d - sindir*d) + camera_data->x;
        float pright_y = (-sindir*d - cosdir*d) + camera_data->y;

        // length of a line segment
        float dx = (pright_x - pleft_x) / w;
        float dy = (pright_y - pleft_y) / w;

        for (int x = 0; x < w; x++) {
            SDL_Color height_map_color = map_get_coords(camera_data->height_map, pleft_x/2, pleft_y/2);
            int column_height = (camera_data->z - (float)height_map_color.r) / (float)d * SCALE_HEIGHT + HORIZON;
            if (column_height < y_buffer[x]) {
                SDL_Color color_map_color = map_get_coords(camera_data->color_map, pleft_x, pleft_y);
                SDL_SetRenderDrawColor(engine->ren, color_map_color.r, color_map_color.g, color_map_color.b, 255);
                SDL_RenderDrawLine(engine->ren, x, column_height, x, y_buffer[x]);
                y_buffer[x] = column_height;
            }
            pleft_x += dx;
            pleft_y += dy;
        }
        //logger_log_i(logger, DEBUG, (int)(dd*1000));
        dd *= 1.01;
    }
}

static void camera_terrain_free(void* entity) {
    Camera_Terrain_Data* camera_data = (Camera_Terrain_Data*)((Entity*)entity)->entity_data;
    free(camera_data);
    ((Entity*)entity)->entity_data = NULL;
}

Entity* camera_terrain_new(Engine* engine, int x, int y, int z, float dir, Map* height_map, Map* color_map) {
    Entity* camera = entity_new(engine, ENTTYPE_CAMERA, camera_terrain_init, camera_terrain_update, camera_terrain_draw, camera_terrain_free);
    Camera_Terrain_Data* camera_data = malloc(sizeof(Camera_Terrain_Data));
    *camera_data = (Camera_Terrain_Data){
        .x = x,
        .y = y,
        .z = z,
        .dir = dir,
        .height_map = height_map,
        .color_map = color_map
    };
    camera->entity_data = camera_data;

    return camera;
}
