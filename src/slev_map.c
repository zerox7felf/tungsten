#include "slev_map.h"
#include <SDL2/SDL.h>
#include <stdlib.h>
#include "map.h"

Slev_Map* slev_map_from_hc_maps(Map* color_map, Map* height_map, int w, int h) {
    Slev_Map_Point* map = (Slev_Map_Point*)malloc(sizeof(Slev_Map_Point)*w*h);
    for (int x; x < w; x++) {
        for(int y; y < h; y++) {
            map[x*y] = (Slev_Map_Point){
                .height = map_get_coords(height_map, x, y).r,
                .color = map_get_coords(color_map, x, y)
            };
        }
    }

    Slev_Map* slev_map = (Slev_Map*)malloc(sizeof(Slev_Map));
    *slev_map = (Slev_Map){
        .version_major = MAJ_VER,
        .version_minor = MIN_VER,
        .w = w, .h = h,
        .map = map
    };

    return slev_map;
}

void slev_map_free(Slev_Map* map) {
    free(map->map);
    free(map);
}
