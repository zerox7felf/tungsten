#include <log.h>
#include <engine.h>

int main() {
    Logger log = logger_new(DEBUG); 
    Engine engine = engine_new(&log);

    if (engine_init(&engine) == 0) {
        logger_log(&log, DEBUG, "Success!");
        engine_run(&engine);
    }

    engine_quit(&engine);
}
