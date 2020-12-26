#include "log.h"
#include "engine.h"
#include "entity.h"
#include "lambda.h"
#include "player.h"
#include "map.h"
#include "slev_map.h"
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

    Map* test_map = map_new_bmp("test4.png");
    Map* test_map_color = map_new_bmp("test4_color.png");

    //Entity* camera_terrain = camera_terrain_new(engine, 250, 400, 200, 0, test_map, test_map_color);
    //Slev_Map* map = slev_map_from_hc_maps(test_map_color, test_map, test_map->surface->w, test_map->surface->h);
    Slev_Map* map = slev_map_from_file("testmap.slev");

    Entity* camera_terrain = camera_terrain_new(engine, 250, 400, 200, 0, map);
    //Entity* debug_map = debug_map_new(engine, map, camera_terrain->entity_data);

    if (engine_init(engine) == 0) {
        logger_log(logger, DEBUG, "Success!");
        //engine_add_entity(engine, player);
        engine_add_entity(engine, camera_terrain);
        //engine_add_entity(engine, debug_map);
        engine_run(engine);
    }

    map_free(test_map);
    map_free(test_map_color);
    slev_map_free(map);
    engine_quit(engine);
}
