#include "log.h"
#include "engine.h"
#include "entity.h"
#include "lambda.h"
#include "player.h"
#include "map.h"
#include "camera_terrain.h"
#include "debug_map.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <assert.h>

Logger* logger;
Engine* engine;

int main() {
    logger = logger_new(DEBUG); 
    engine = engine_new(logger);
    Entity* player = player_new(engine, 200,200,0.5);

    Map* test_map = map_new_bmp("test3.bmp");
    Map* test_map_color = map_new_bmp("test3_color.bmp");

    Entity* camera_terrain = camera_terrain_new(engine, 250, 400, 200, 0, test_map, test_map_color);
    Entity* debug_map = debug_map_new(engine, test_map, camera_terrain->entity_data);

    if (engine_init(engine) == 0) {
        logger_log(logger, DEBUG, "Success!");
        //engine_add_entity(engine, player);
        engine_add_entity(engine, camera_terrain);
        //engine_add_entity(engine, debug_map);
        engine_run(engine);
    }

    map_free(test_map);
    map_free(test_map_color);
    engine_quit(engine);
}
