common: common.c (common.h)
camera_terrain: camera_terrain.c (camera_terrain.h)
debug_map: debug_map.c (debug_map.h)
map: map.c (map.h)
player: player.c (player.h)
entity: entity.c (entity.h)
engine: engine.c (engine.h)
log: log.c (log.h)
controller: controller.c (controller.h)
slev_map: slev_map.c (slev_map.h)

exec tungsten: main.c $common $camera_terrain $debug_map $map $player $entity $engine $log $controller $slev_map
exec slev: slev.c $log $map $common $slev_map
