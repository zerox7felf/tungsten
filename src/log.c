#include "log.h"
#include <stdio.h>
#include <stdlib.h>

Logger* logger_new(Log_Level level) {
    Logger* logger = malloc(sizeof(Logger));
    *logger = (Logger){.level = level};
    return logger;
}

void logger_set_level(Logger* logger, Log_Level level) {
    logger->level = level;
}

static char* log_names[4] = {
    "[DBG]",
    "[INF]",
    "[WAR]",
    "[ERR]"
};

typedef struct {
    char* bright;
    char* faint;
} Log_Color;

static Log_Color log_colors[4] = {
    (Log_Color){.bright = "0",      .faint = "0"        },
    (Log_Color){.bright = "0",      .faint = "0"        },
    (Log_Color){.bright = "103;30", .faint = "43;30"    },
    (Log_Color){.bright = "101;97", .faint = "101;97"   },
};

void logger_log(const Logger* logger, Log_Level level, const char* message) {
    if (level >= logger->level) {
        printf("%c[%sm", 27, log_colors[level].faint);
        printf("%c[2K", 27);
        printf("%c[%sm %s %c[%sm %s", 27, log_colors[level].bright, log_names[level], 27, log_colors[level].faint, message);

        printf("%c[0m\n", 27);
    }
}

void logger_log_i(const Logger* logger, Log_Level level, const int message) {
    if (level >= logger->level) {
        printf("%c[%sm", 27, log_colors[level].faint);
        printf("%c[2K", 27);
        printf("%c[%sm %s %c[%sm %d", 27, log_colors[level].bright, log_names[level], 27, log_colors[level].faint, message);

        printf("%c[0m\n", 27);
    }
}
