#pragma once

#include "entity.h"
#include "engine.h"

typedef void (*Controller_Follow)(Entity* entity, float x, float y, float z, float dir, float dir_vert);

typedef struct {
    float x, y, z;
    float dir, dir_vert;
    Entity** children;
    int num_children;
    int num_alloc;
} Controller_Data;

//TODO: so... we're just slapping an extra variable onto another pointer in order to add extra functionality to an entity...
// if this becomes a common occurance, rework. Will quickly become *very* messy...
typedef struct {
    void* entity_data;
    Controller_Follow follow;
} Controller_Entity_Data;

Entity* controller_new(Engine* engine, float x, float y, float z, float dir, float dir_vert);
void controller_add_child(Entity* controller, Entity* child);

