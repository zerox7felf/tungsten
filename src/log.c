#include "log.h"
#include <stdio.h>
#include <stdlib.h>

Logger* logger_new(Log_Level level) {
    Logger* logger = malloc(sizeof(Logger));
    *logger = (Logger){.level = level};
    //printf("\n");   //So that we have a new line to clear when outputting first log msg
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

void logger_log(const Logger* logger, Log_Level level, const char* message) {
    if (level >= logger->level) {
        if (level == ERROR) 
            printf("%c[101;97m", 27);
        else if (level == WARN)
            printf("%c[103;30m", 27);
        printf("%c[2K", 27);

        printf("%s: %s", log_names[level], message);
        printf("%c[0m\n", 27);
    }
}

void logger_log_i(const Logger* logger, Log_Level level, const int message) {
    if (level >= logger->level) {
        if (level == ERROR) 
            printf("%c[101;97m", 27);
        else if (level == WARN)
            printf("%c[103;30m", 27);
        printf("%c[2K", 27);

        printf("%s: %d", log_names[level], message);
        printf("%c[0m\n", 27);
    }
}
