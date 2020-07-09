#include "entity.h"
#include <stdlib.h>

Entity* entity_new(void* engine, int entity_type, Entity_Init init, Entity_Update update, Entity_Draw draw, Entity_Free free) {
    Entity* entity = malloc(sizeof(Entity));
    *entity = (Entity){
        .type = entity_type,
        .engine = engine,
        .state = UNINITIALIZED,
        .init = init,
        .update = update,
        .draw = draw,
        .free = free
    };
    return entity;
}
