#include "entity.h"
#include "player.h"
#include "log.h"
#include "engine.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

extern Logger* logger;

static void player_init(void* entity) {
}

static void player_update(void* entity, int dt) {
    Player_Data* player_data = ((Entity*)entity)->entity_data;
    Engine* engine = ((Entity*)entity)->engine;
    if (engine->keyboard_state[SDL_SCANCODE_W])
        player_data->y--;
    if (engine->keyboard_state[SDL_SCANCODE_S])
        player_data->y++;
    if (engine->keyboard_state[SDL_SCANCODE_D])
        player_data->x++;
    if (engine->keyboard_state[SDL_SCANCODE_A])
        player_data->x--;
}

static void player_draw(void* entity, int dt) {
    Player_Data* player_data = ((Entity*)entity)->entity_data;
    Engine* engine = ((Entity*)entity)->engine;
    SDL_SetRenderDrawColor(engine->ren, 255, 0, 0, 0);
    SDL_Rect rect = {player_data->x, player_data->y, 50, 50};
    SDL_RenderFillRect(engine->ren, &rect);
}

static void player_free(void* entity) {
}

Entity* player_new(void* engine, int x, int y, float speed) {
    Entity* player = entity_new(
        engine,
        ENTTYPE_PLAYER,
        player_init,
        player_update,
        player_draw,
        player_free
    );

    Player_Data* player_data = malloc(sizeof(Player_Data));
    *player_data = (Player_Data){
        .y = y, .x = x, .speed = speed
    };
    player->entity_data = player_data;

    return player;
}
