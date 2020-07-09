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
    "[DEBG]",
    "[INFO]",
    "[WARN]",
    "[ERRO]"
};

void logger_log(const Logger* logger, Log_Level level, const char* message) {
    if (level >= logger->level)
        printf("%s:\t%s\n", log_names[level], message);
}

void logger_log_i(const Logger* logger, Log_Level level, const int message) {
    if (level >= logger->level)
        printf("%s:\t%d\n", log_names[level], message);
}
