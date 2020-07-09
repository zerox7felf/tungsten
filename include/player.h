#include "entity.h"

typedef struct {
    int x,y;
    float speed;
} Player_Data;

Entity* player_new(void* engine, int x, int y, float speed);
