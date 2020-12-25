#include "log.h"
#include "map.h"
#include "slev_map.h"
#include <SDL2/SDL.h>

// Slev is the mapmaker for tungsten, combining heightmaps and colormaps into a single binary format.
// Usage:
//  slev <heightmap> <colormap> <output mapname>

Logger* logger;

int main(int argc, char* argv[]) {
    logger = logger_new(DEBUG);

    if (argc < 4) {
        logger_log(logger, ERROR, "Not enough arguments! Usage: slev <heightmap> <colormap> <output mapname>");
        return 1;
    }

    Map* height_map = map_new_bmp(argv[1]);
    if (height_map == NULL) {
        logger_log(logger, ERROR, "Failed to load heightmap");
        return 1;
    } else {
        logger_log(logger, INFO, "Loaded heightmap");
    }

    Map* color_map = map_new_bmp(argv[2]);
    if (color_map == NULL) {
        logger_log(logger, ERROR, "Failed to load colormap");
        return 1;
    } else {
        logger_log(logger, INFO, "Loaded colormap");
    }

    int color_map_width = 0;    // -1: thinner, 0: same as height_map, 1: wider
    int color_map_height = 0;   // -1: shorter, 0: same as height_map, 1: taller

    color_map_width =   color_map->surface->w > height_map->surface->w ?  1 :
                        color_map->surface->w < height_map->surface->w ? -1 : 0;
    color_map_height =  color_map->surface->h > height_map->surface->h ?  1 :
                        color_map->surface->h < height_map->surface->h ? -1 : 0;

    // crop to shortest. use these for calculations later.
    int map_width = color_map_width == -1 ? color_map->surface->w : height_map->surface->w;
    int map_height = color_map_height == -1 ? color_map->surface->h : height_map->surface->h;

    if (color_map_width != 0 && color_map_height != 0) {
        logger_log(logger, INFO, "Images are of different sizes. Crop to smallest common dimensions?");
        Logger_Option options[2] = {
            (Logger_Option){.option='y', .description="Yes", .is_default=true},
            (Logger_Option){.option='n', .description="No", .is_default=false}
        };
        Logger_Option opt = logger_prompt(logger, INFO, options, 2);

        if (opt.option == 'n') {
            logger_log(logger, ERROR, "Mapsizes do not match.");
            map_free(color_map);
            map_free(height_map);
            return 1;
        }
    }

    logger_log(logger, INFO, "Loading height and color map into slev format...");
    Slev_Map* output_map = slev_map_from_hc_maps(color_map, height_map, map_width, map_height);
    
    slev_map_free(output_map);
    map_free(color_map);
    map_free(height_map);

    return 0;
}
