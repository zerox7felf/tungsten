#pragma once

typedef void (*Entity_Init)(void* entity);
typedef void (*Entity_Update)(void* entity, int dt);
typedef void (*Entity_Draw)(void* entity, int dt);
typedef void (*Entity_Free)(void* entity);

typedef enum {
    UNINITIALIZED = 0,
    ALIVE,
    DEAD
} Entity_State;

#define ENTTYPE_NONE 0
#define ENTTYPE_PLAYER 1
#define ENTTYPE_CAMERA 2
// ^- make enum? Will we ever use these?
// replace enttype lookups with expressed relations through data structures. (?)

typedef struct {
    int id;
    int type;
    void* entity_data;
    void* engine;       // lots of void pointers here... any better way to solve this?
    Entity_State state;
    Entity_Init init;
    Entity_Update update;
    Entity_Draw draw;
    Entity_Free free;
} Entity;

Entity* entity_new(void* engine, int entity_type, Entity_Init init, Entity_Update update, Entity_Draw draw, Entity_Free free);
