#pragma once

typedef void (*Entity_Update)(int dt);
typedef void (*Entity_Draw)(int dt);

typedef enum {
    UNINITIALIZED = 0,
    ALIVE,
    DEAD
} Entity_State;

typedef struct {
    int id;
    Entity_State state;
    Entity_Update update;
    Entity_Draw draw;
} Entity;

Entity entity_new(Entity_Update update, Entity_Draw draw);
