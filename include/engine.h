#pragma once

#include "entity.h"
#include "log.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>

typedef struct {
    Entity** entities;
    int entities_allocated;
    int num_entities;
    int entities_made;
    SDL_Window* win;
    SDL_Renderer* ren;
    TTF_Font* font;
    Logger* log;
    Uint32 last_update;
    Uint32 last_draw;
    const Uint8* keyboard_state;
    int running;
} Engine;

Engine* engine_new(Logger* log);
int engine_init(Engine* engine);
void engine_quit(Engine* engine);
void engine_update(Engine* engine);
void engine_draw(Engine* engine);
void engine_run(Engine* engine);
void engine_stop(Engine* engine);
void engine_handle_events(Engine* engine);
void engine_add_entity(Engine* engine, Entity* entity);
Entity* engine_get_entity(Engine* engine, int id);
