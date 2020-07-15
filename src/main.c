#include "log.h"
#include "engine.h"
#include "entity.h"
#include "lambda.h"
#include "player.h"
#include "map.h"
#include "camera_terrain.h"
#include <SDL2/SDL.h>
#include <assert.h>

Logger* logger;
Engine* engine;

int main() {
    logger = logger_new(DEBUG); 
    engine = engine_new(logger);
    Entity* player = player_new(engine, 200,200,0.5);

    Map* test_map = map_new_bmp("test.bmp");
    Map* test_map_color = map_new_bmp("test_color.bmp");
    Entity* map_viewer = entity_new(
        engine, ENTTYPE_NONE, NULL, NULL,
        lambda(void, (void* entity, int dt), {
            Map* map = (Map*)((Entity*)entity)->entity_data;
            for (int x = 0; x < map->surface->w; x++) {
                for (int y = 0; y < map->surface->h; y++) {
                    SDL_Color color = map_get_coords(map, x, y);
                    SDL_SetRenderDrawColor(engine->ren, color.r, color.g, color.b, 255);
                    SDL_RenderDrawPoint(engine->ren, x, y);
                }
            }
        }),
        NULL
    );
    Entity* camera_terrain = camera_terrain_new(engine, 250, 400, 200, 0, test_map, test_map_color);
    map_viewer->entity_data = test_map_color;

    if (engine_init(engine) == 0) {
        logger_log(logger, DEBUG, "Success!");
        //engine_add_entity(engine, player);
        engine_add_entity(engine, camera_terrain);
        //engine_add_entity(engine, map_viewer);
        engine_run(engine);
    }

    map_free(test_map);
    map_free(test_map_color);
    engine_quit(engine);
}
