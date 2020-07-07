#pragma once
#include <entity.h>
#include <log.h>
#include <SDL2/SDL.h>

typedef struct {
    Entity* entities;
    int numEntities;
    SDL_Window* win;
    SDL_Renderer* ren;
    Logger* log;
    Uint32 last_update;
    Uint32 last_draw;
    int running;
} Engine;

Engine engine_new(Logger* log);
int engine_init(Engine* engine);
void engine_quit(Engine* engine);
void engine_update(Engine* engine);
void engine_draw(Engine* engine);
void engine_run(Engine* engine);
void engine_stop(Engine* engine);
void engine_handle_events(Engine* engine);
