#include "entity.h"
#include <stdlib.h>

Entity* entity_new(Entity_Init init, Entity_Update update, Entity_Draw draw, Entity_Free free) {
    Entity* entity = malloc(sizeof(Entity));
    *entity = (Entity){
        .state = UNINITIALIZED,
        .init = init,
        .update = update,
        .draw = draw,
        .free = free
    };
    return entity;
}
