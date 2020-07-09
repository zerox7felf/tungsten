#include "engine.h"
#include "entity.h"
#include "log.h"
#include <SDL2/SDL.h>
#include <assert.h>

Engine* engine_new(Logger* log) {
    Engine* engine = malloc(sizeof(Engine));
    *engine = (Engine) {
        .entities = NULL,
        .entities_allocated = 0,
        .num_entities = 0,
        .entities_made = 0,
        .win = NULL,
        .ren = NULL,
        .log = log,
        .last_update = 0,
        .last_draw = 0,
        .running = 0
    };
    return engine;
}

int engine_init(Engine* engine) {
    logger_log(engine->log, INFO, "Initializing");
    if(SDL_Init(SDL_INIT_VIDEO) != 0) {
        logger_log(engine->log, ERROR, "Couldn't initialize SDL:");
        logger_log(engine->log, ERROR, SDL_GetError());
        return 1;
    }

    engine->win = SDL_CreateWindow("tungsten", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, 0);
    if (engine->win == NULL) {
        logger_log(engine->log, ERROR, "Couldn't create window:");
        logger_log(engine->log, ERROR, SDL_GetError());
        return 1;
    }

    engine->ren = SDL_CreateRenderer(engine->win, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (engine->ren == NULL) {
        logger_log(engine->log, ERROR, "Couldn't create renderer:");
        logger_log(engine->log, ERROR, SDL_GetError());
        return 1;
    }

    engine->keyboard_state = SDL_GetKeyboardState(NULL);

    return 0;
}

void engine_quit(Engine* engine) {
    logger_log(engine->log, INFO, "Quitting");

    if (engine->entities != NULL) {
        for (int i = 0; i < engine->num_entities; i++) {
            if (engine->entities[i] != NULL && engine->entities[i]->free != NULL) {
                engine->entities[i]->free(engine->entities[i]);
                free(engine->entities[i]);
            }
        }
        free(engine->entities);
        engine->entities = NULL;
    }

    if (engine->ren != NULL)
        SDL_DestroyRenderer(engine->ren);
    if (engine->win != NULL)
        SDL_DestroyWindow(engine->win);

    SDL_Quit();
    free(engine);
}

void engine_update(Engine* engine) {
    logger_log(engine->log, DEBUG, "Update");
    Uint32 now = SDL_GetTicks();
    int dt = now - engine->last_update;
    logger_log_i(engine->log, DEBUG, dt);

    // TODO: update entities
    if (engine->entities != NULL) {
        for (int i = 0; i < engine->num_entities; i++) {
            if (engine->entities[i] != NULL) {
                if (engine->entities[i]->update != NULL)
                    engine->entities[i]->update(engine->entities[i], dt);
            }
        }
    }

    engine->last_update = now;
}

void engine_draw(Engine* engine) {
    logger_log(engine->log, DEBUG, "Draw");
    Uint32 now = SDL_GetTicks();
    int dt = now - engine->last_draw;
    logger_log_i(engine->log, DEBUG, dt);

    SDL_SetRenderDrawColor(engine->ren, 0, 0, 0, 0);
    SDL_RenderClear(engine->ren);

    // TODO: draw entities
    if (engine->entities != NULL) {
        for (int i = 0; i < engine->num_entities; i++) {
            if (engine->entities[i] != NULL && engine->entities[i]->draw != NULL)
                engine->entities[i]->draw(engine->entities[i], dt);
        }
    }

    SDL_RenderPresent(engine->ren);
    engine->last_draw = now;
}

void engine_run(Engine* engine) {
    engine->running = 1;
    while (engine->running) {
        engine_update(engine);
        engine_draw(engine);
        engine_handle_events(engine);
        SDL_Delay(16); //TODO: compensate for time lost in update and draw
    }
}

void engine_stop(Engine* engine) {
    engine->running = 0;
}

void engine_handle_events(Engine* engine) { //TODO: keyboard events for entities
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                engine_stop(engine);
                break;
        }
    }
}

void engine_add_entity(Engine* engine, Entity* entity) {
    logger_log(engine->log, DEBUG, "Adding entity. State:");
    logger_log_i(engine->log, DEBUG, entity->state);
    assert(entity->state == UNINITIALIZED);

    entity->id = engine->entities_made++;
    logger_log(engine->log, DEBUG, "entities_made:");
    logger_log_i(engine->log, DEBUG, engine->entities_made);

    engine->num_entities++;
    if (engine->num_entities > engine->entities_allocated) {
        if (engine->entities == NULL) {
            engine->entities = malloc(engine->num_entities * sizeof(Entity*));
        } else {
            engine->entities = realloc(engine->entities, engine->num_entities * sizeof(Entity*));
        }
    }

    engine->entities[engine->num_entities-1] = entity;
    if (entity->init != NULL)
        entity->init(entity);
}

Entity* engine_get_entity(Engine* engine, int id) {
    for (int i = 0; i < engine->num_entities; i++) {
        if (engine->entities[i]->id == id)
            return engine->entities[i];
    }
    return NULL;
}
