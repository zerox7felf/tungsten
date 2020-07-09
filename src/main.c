#include "log.h"
#include "engine.h"
#include "entity.h"
#include "lambda.h"
#include "player.h"
#include <SDL2/SDL.h>
#include <assert.h>

Logger* logger;
Engine* engine;

int main() {
    logger = logger_new(DEBUG); 
    engine = engine_new(logger);
    Entity* player = player_new(engine, 200,200,0.5);

    if (engine_init(engine) == 0) {
        logger_log(logger, DEBUG, "Success!");
        engine_add_entity(engine, player);
        engine_run(engine);
    }

    engine_quit(engine);
}
