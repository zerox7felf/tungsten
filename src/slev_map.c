#include "slev_map.h"
#include <SDL2/SDL.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "map.h"
#include "log.h"
#include "common.h"

extern Logger* logger;

Slev_Map* slev_map_from_hc_maps(Map* color_map, Map* height_map, int w, int h) {
    logger_log(logger, INFO, "Loading height and color map into slev format...");
    Slev_Map_Point* map = (Slev_Map_Point*)malloc(sizeof(Slev_Map_Point)*w*h);
    for (int x = 0; x < w; x++) {
        for(int y = 0; y < h; y++) {
            map[x + y*w] = (Slev_Map_Point){
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

Slev_Map* slev_map_from_file(const char* src) {
    FILE* fp = fopen(src, "r");
    logger_log(logger, DEBUG, "Opening file for reading...");
    if (fp == NULL) return false;

    Slev_Map* slev_map = (Slev_Map*)malloc(sizeof(Slev_Map));
    char* magicNum[6];
    logger_log(logger, DEBUG, "Reading magic...");
    if (fread(&magicNum, 1, 6, fp) != 6){free(slev_map); return NULL;}; // Read magic thingy
    logger_log(logger, DEBUG, "Reading version number...");
    if (fread(&(slev_map->version_major), sizeof(int), 1, fp) != 1){free(slev_map); return NULL;}; // Version number
    if (fread(&(slev_map->version_minor), sizeof(int), 1, fp) != 1){free(slev_map); return NULL;}; // Version number
    logger_log(logger, DEBUG, "Version (Major, Minor):");
    logger_log_i(logger, DEBUG, slev_map->version_major);
    logger_log_i(logger, DEBUG, slev_map->version_minor);
    logger_log(logger, DEBUG, "Reading map dimensions...");
    if (fread(&(slev_map->w), sizeof(int), 1, fp) != 1){free(slev_map); return NULL;}; // Map Width
    if (fread(&(slev_map->h), sizeof(int), 1, fp) != 1){free(slev_map); return NULL;}; // Map Height

    logger_log(logger, DEBUG, "Allocating map...");
    slev_map->map = (Slev_Map_Point*)malloc(sizeof(Slev_Map_Point)*slev_map->w*slev_map->h);
    //for(int i = 0; i < slev_map->w*slev_map->h; i++) {
    logger_log(logger, DEBUG, "Reading map...");
    if (fread(slev_map->map, sizeof(Slev_Map_Point), slev_map->w*slev_map->h, fp) != slev_map->w*slev_map->h){free(slev_map->map); free(slev_map); return NULL;};
    //}
    logger_log(logger, DEBUG, "Done");
    fclose(fp);

    return slev_map;
}

Slev_Map_Point slev_map_get_coords(Slev_Map* map, int x, int y) {
    x = mod(x, map->w);
    y = mod(y, map->h);

    return map->map[x + y*map->w];
}

bool Slev_map_save(Slev_Map* map, const char* dest) {
    logger_log(logger, DEBUG, "Opening file for writing...");
    FILE* fp = fopen(dest, "w");
    if (fp == NULL) return false;
    
    logger_log(logger, DEBUG, "Writing magic...");
    if (fwrite("SLEV!", 6, 1, fp) != 1) return false;
    logger_log(logger, DEBUG, "Writing version number...");
    if (fwrite(&(map->version_major), sizeof(int), 1, fp) != 1) return false;
    if (fwrite(&(map->version_minor), sizeof(int), 1, fp) != 1) return false;
    logger_log(logger, DEBUG, "Writing map dimensions...");
    if (fwrite(&(map->w), sizeof(int), 1, fp) != 1) return false;
    if (fwrite(&(map->h), sizeof(int), 1, fp) != 1) return false;

    logger_log(logger, DEBUG, "Writing map...");
    if (fwrite(map->map, sizeof(Slev_Map_Point), map->w*map->h, fp) != map->w*map->h) return false;

    logger_log(logger, DEBUG, "Done");
    fclose(fp);

    return true;
}

void slev_map_free(Slev_Map* map) {
    free(map->map);
    free(map);
}
