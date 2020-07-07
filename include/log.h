#pragma once

typedef enum {
    DEBUG = 0,
    INFO = 1,
    WARN = 2,
    ERROR = 3
} Log_Level;

typedef struct {
    Log_Level level;  // The minimum level at which to generate output
} Logger;

Logger logger_new(Log_Level level);
void logger_set_level(Logger* logger, Log_Level level);
void logger_log(const Logger* logger, Log_Level level, const char* message);
void logger_log_i(const Logger* logger, Log_Level level, const int message);
