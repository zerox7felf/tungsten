#pragma once

typedef struct {
    int id;
    void (*update)(int dt);
    void (*draw)(int dt);
} Entity;
