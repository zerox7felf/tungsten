#include <stdlib.h>
#include <stdio.h>
#include "controller.h"
#include "entity.h"
#include "lambda.h"
#include "log.h"
#include "engine.h"

extern Logger* logger;

static void controller_update(void* entity, int dt) {
    Controller_Data* controller_data = (Controller_Data*) ((Entity*)entity)->entity_data;
    Engine* engine = ((Entity*)entity)->engine;

    float move_dist = 0.012*dt;
    if (engine->keyboard_state[SDL_SCANCODE_LSHIFT])
        move_dist *= 1.7;

    if (engine->keyboard_state[SDL_SCANCODE_W]) {
        //controller_data->y--;
        float dy = move_dist * cosf(controller_data->dir);
        float dx = move_dist * sinf(controller_data->dir);
        controller_data->y -= dy;
        controller_data->x -= dx;
    }

    if (engine->keyboard_state[SDL_SCANCODE_S]) {
        //controller_data->y++;
        float dy = move_dist * cosf(controller_data->dir);
        float dx = move_dist * sinf(controller_data->dir);
        controller_data->y += dy;
        controller_data->x += dx;
    }

    if (engine->keyboard_state[SDL_SCANCODE_D]) {
        //controller_data->x++;
        float dy = move_dist * cosf(3.1415f/2 + controller_data->dir);
        float dx = move_dist * sinf(3.1415f/2 + controller_data->dir);
        controller_data->y += dy;
        controller_data->x += dx;
    }

    if (engine->keyboard_state[SDL_SCANCODE_A]) {
        //controller_data->x--;
        float dy = move_dist * cosf(3.1415f/2 + controller_data->dir);
        float dx = move_dist * sinf(3.1415f/2 + controller_data->dir);
        controller_data->y -= dy;
        controller_data->x -= dx;
    }

    if (engine->keyboard_state[SDL_SCANCODE_Z])
        controller_data->z += move_dist;
    if (engine->keyboard_state[SDL_SCANCODE_X])
        controller_data->z -= move_dist;

    if (engine->keyboard_state[SDL_SCANCODE_LEFT])
        controller_data->dir+=.1;
    if (engine->keyboard_state[SDL_SCANCODE_RIGHT])
        controller_data->dir-=.1;
    if (engine->keyboard_state[SDL_SCANCODE_UP])
        controller_data->dir_vert+=5;
    if (engine->keyboard_state[SDL_SCANCODE_DOWN])
        controller_data->dir_vert-=5;

    controller_data->dir = fmodf(controller_data->dir, 2*3.1415f);

    //controller_data->z = map_get_coords(controller_data->height_map, controller_data->x*VOXEL_DENSITY*HEIGHTMAP_SCALE, controller_data->y*VOXEL_DENSITY*HEIGHTMAP_SCALE).r + 10;
    //controller_data->z = controller_data->map->map[(int)(controller_data->x*VOXEL_DENSITY)*(int)(controller_data->y*VOXEL_DENSITY)].height + 10;
    //controller_data->z = slev_map_get_coords(controller_data->map, (int)(controller_data->x*VOXEL_DENSITY), (int)(controller_data->y*VOXEL_DENSITY)).height + 10;

    if (controller_data->children != NULL) {
        for (int i = 0; i < controller_data->num_children; i++) {
            ((Controller_Entity_Data*) controller_data->children[i]->entity_data)->follow(
                controller_data->children[i],
                controller_data->x,
                controller_data->y,
                controller_data->z,
                controller_data->dir,
                controller_data->dir_vert
            );
        }
    }
}

static void controller_free(void* entity) {
    Controller_Data* controller_data = (Controller_Data*) ((Entity*)entity)->entity_data;
    free(controller_data->children);
    free(controller_data);
}

Entity* controller_new(Engine* engine, float x, float y, float z, float dir, float dir_vert) {
    Entity* entity = entity_new(engine, ENTTYPE_NONE, NULL, controller_update, NULL, controller_free);
    
    Controller_Data* controller_data = malloc(sizeof(Controller_Data));
    *controller_data = (Controller_Data){
        .x = x,
        .y = y,
        .z = z,
        .dir = dir,
        .dir_vert = dir_vert,
        .num_children = 0,
        .num_alloc = 0,
        .children = NULL
    };
    entity->entity_data = controller_data;

    return entity;
}

void controller_add_child(Entity* controller, Entity* child) {
    Controller_Data* controller_data = (Controller_Data*)controller->entity_data;
    controller_data->num_children++;
    if (controller_data->num_alloc < controller_data->num_children) {
        controller_data->children = realloc(controller_data->children, controller_data->num_children*sizeof(Entity*));
        controller_data->num_alloc = controller_data->num_children;
    }
    controller_data->children[controller_data->num_children - 1] = child;
}
