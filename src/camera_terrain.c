#include "common.h"
#include "map.h"
#include "camera_terrain.h"
#include "entity.h"
#include "engine.h"
#include "log.h"
#include <stdio.h>
#include <string.h>
#include <SDL2/SDL.h>
#include <stdbool.h>

#define HORIZON 120
#define SCALE_HEIGHT 70.0
#define DISTANCE 400
#define VOXEL_DENSITY 6
#define HEIGHTMAP_SCALE 1

extern Logger* logger;

static void camera_terrain_init(void* entity) {
}

static void camera_terrain_update(void* entity, int dt) {
    Camera_Terrain_Data* camera_data = (Camera_Terrain_Data*)((Entity*)entity)->entity_data;
    Engine* engine = ((Entity*)entity)->engine;

    float move_dist = 0.012*dt;
    if (engine->keyboard_state[SDL_SCANCODE_LSHIFT])
        move_dist *= 1.7;

    if (engine->keyboard_state[SDL_SCANCODE_W]) {
        //camera_data->y--;
        float dy = move_dist * cosf(camera_data->dir);
        float dx = move_dist * sinf(camera_data->dir);
        camera_data->y -= dy;
        camera_data->x -= dx;
    }

    if (engine->keyboard_state[SDL_SCANCODE_S]) {
        //camera_data->y++;
        float dy = move_dist * cosf(camera_data->dir);
        float dx = move_dist * sinf(camera_data->dir);
        camera_data->y += dy;
        camera_data->x += dx;
    }

    if (engine->keyboard_state[SDL_SCANCODE_D]) {
        //camera_data->x++;
        float dy = move_dist * cosf(3.1415f/2 + camera_data->dir);
        float dx = move_dist * sinf(3.1415f/2 + camera_data->dir);
        camera_data->y += dy;
        camera_data->x += dx;
    }

    if (engine->keyboard_state[SDL_SCANCODE_A]) {
        //camera_data->x--;
        float dy = move_dist * cosf(3.1415f/2 + camera_data->dir);
        float dx = move_dist * sinf(3.1415f/2 + camera_data->dir);
        camera_data->y -= dy;
        camera_data->x -= dx;
    }

    if (engine->keyboard_state[SDL_SCANCODE_LEFT])
        camera_data->dir+=.1;
    if (engine->keyboard_state[SDL_SCANCODE_RIGHT])
        camera_data->dir-=.1;
    if (engine->keyboard_state[SDL_SCANCODE_UP])
        camera_data->dir_vert+=5;
    if (engine->keyboard_state[SDL_SCANCODE_DOWN])
        camera_data->dir_vert-=5;

    camera_data->dir = fmodf(camera_data->dir, 2*3.1415f);
    camera_data->z = map_get_coords(camera_data->height_map, camera_data->x*VOXEL_DENSITY*HEIGHTMAP_SCALE, camera_data->y*VOXEL_DENSITY*HEIGHTMAP_SCALE).r + 10;
}

static void camera_terrain_draw(void* entity, int dt) {
    Camera_Terrain_Data* camera_data = (Camera_Terrain_Data*)((Entity*)entity)->entity_data;
    Engine* engine = (Engine*)((Entity*)entity)->engine;

    int w,h;
    SDL_GetRendererOutputSize(engine->ren, &w, &h);
    SDL_RenderSetScale(engine->ren, 4, 4);
    w/=4;
    h/=4;

    float sindir = sinf(camera_data->dir);
    float cosdir = cosf(camera_data->dir);

    SDL_Color fog_color = {.r = 200, .g = 200, .b = 255};
    SDL_Color sky_color = {.r = 200, .g = 200, .b = 255};

    SDL_SetRenderDrawColor(engine->ren, sky_color.r, sky_color.g, sky_color.b, 255);
    SDL_RenderClear(engine->ren);

    int y_buffer[w];
    for (int i = 0; i < w; i++)
        y_buffer[i] = h;

    float dd = 0.125; // delta-d
    float render_detail = 1.0;
    bool seam_transition = false; // true if we have transitioneed between two levels of render_detail, which will cause a seam to appear.
    for (float d = 1.0; d < DISTANCE; d+=dd) {
        // line on map
        float pleft_x, pleft_y;
        float pright_x, pright_y;

        pleft_x = (-cosdir*d- sindir*d) + camera_data->x;
        pleft_y = ( sindir*d- cosdir*d) + camera_data->y;

        pright_x = ( cosdir*d- sindir*d) + camera_data->x;
        pright_y = (-sindir*d- cosdir*d) + camera_data->y;

        // length of a line segment
        float dx = (pright_x - pleft_x) / (w/(int)render_detail);
        float dy = (pright_y - pleft_y) / (w/(int)render_detail);

        for (int x = 0; x < w; x+=(int)render_detail) {
            SDL_Color height_map_color;
            height_map_color = map_get_coords(camera_data->height_map, pleft_x*VOXEL_DENSITY*HEIGHTMAP_SCALE, pleft_y*VOXEL_DENSITY*HEIGHTMAP_SCALE);
            int column_height = (camera_data->z - (float)height_map_color.r) / (float)d * SCALE_HEIGHT + HORIZON + camera_data->dir_vert;

            if (column_height < y_buffer[x]) {
                SDL_Color color_map_color;
                color_map_color = map_get_coords(camera_data->color_map, pleft_x*VOXEL_DENSITY*HEIGHTMAP_SCALE, pleft_y*VOXEL_DENSITY*HEIGHTMAP_SCALE);
                float fog_factor = d/DISTANCE;
                color_map_color.r = fog_color.r*fog_factor + color_map_color.r*(1-fog_factor);
                color_map_color.g = fog_color.g*fog_factor + color_map_color.g*(1-fog_factor);
                color_map_color.b = fog_color.b*fog_factor + color_map_color.b*(1-fog_factor);

                SDL_SetRenderDrawColor(engine->ren, color_map_color.r, color_map_color.g, color_map_color.b, 255);
                SDL_Rect rect = {.x = x, .y = column_height, .w = (int)render_detail, .h = y_buffer[x]-column_height};
                if (seam_transition)
                    rect.h+=2;

                SDL_RenderFillRect(engine->ren, &rect);
                for (int buffer_pos = 0; buffer_pos < render_detail; buffer_pos++)
                    y_buffer[x+buffer_pos] = column_height;
            }
            pleft_x += dx;
            pleft_y += dy;
        }

        /*seam_transition = false;
        if (d > 150) {
            dd = 2;
            seam_transition = true;
        } else if (d > 75) {
            dd = 1;
            seam_transition = true;
        } else if (d > 30) {
            dd = 0.5;
            seam_transition = true;
        } else if (d > 15) {
            dd = 0.2;
        }*/
        dd *= 1.005;
    }

    SDL_RenderSetScale(engine->ren, 1, 1);
}

static void camera_terrain_free(void* entity) {
    Camera_Terrain_Data* camera_data = (Camera_Terrain_Data*)((Entity*)entity)->entity_data;
    free(camera_data);
    ((Entity*)entity)->entity_data = NULL;
}

Entity* camera_terrain_new(Engine* engine, int x, int y, int z, float dir, Map* height_map, Map* color_map ) {
    Entity* camera = entity_new(engine, ENTTYPE_CAMERA, camera_terrain_init, camera_terrain_update, camera_terrain_draw, camera_terrain_free);
    Camera_Terrain_Data* camera_data = malloc(sizeof(Camera_Terrain_Data));
    *camera_data = (Camera_Terrain_Data){
        .x = x,
        .y = y,
        .z = z,
        .dir = dir,
        .dir_vert = 0,
        .height_map = height_map,
        .color_map = color_map,
    };
    camera->entity_data = camera_data;

    return camera;
}
