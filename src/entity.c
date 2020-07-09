#include "entity.h"

Entity entity_new(Entity_Update update, Entity_Draw draw) {
    return (Entity){
        .state = UNINITIALIZED,
        .update = update,
        .draw = draw
    };
}
