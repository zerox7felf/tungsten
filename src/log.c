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
    (Log_Color){.bright = "46;97",  .faint = "104;97"   },
    (Log_Color){.bright = "103;30", .faint = "43;30"    },
    (Log_Color){.bright = "101;97", .faint = "41;97"    },
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

Logger_Option logger_prompt(const Logger* logger, Log_Level level, const Logger_Option* options, const int n_options) {
    // getch, ret char if in options, else ret def_option
    if (level >= logger->level) {
        int default_index = -1;
        for (int i = 0; i < n_options; i++) {
            printf("%c[%sm", 27, log_colors[level].faint);
            printf("%c[2K", 27);
            if (options[i].is_default) {
                default_index = i;
                printf("%c[%sm %c %c[%sm (Default) %s", 27, log_colors[level].bright, options[i].option, 27, log_colors[level].faint, options[i].description);
            } else {
                printf("%c[%sm %c %c[%sm %s", 27, log_colors[level].bright, options[i].option, 27, log_colors[level].faint, options[i].description);
            }

            printf("%c[0m\n", 27);
        }

        printf("%c[%sm", 27, log_colors[level].faint);
        printf("%c[2K", 27);
        printf("%c[%sm %s %c[%sm ", 27, log_colors[level].bright, ">", 27, log_colors[level].faint);

        char opt = (char)getchar();
        if (opt != '\n') while(getchar() != '\n');

        printf("%c[1F%c[0m\n", 27, 27);

        for (int i = 0; i < n_options; i++) {
            if (opt == options[i].option) return options[i];
        }

        if (default_index == -1) return options[0];
        else return options[default_index];
    } else {
        int default_index = -1;
        for (int i = 0; i < n_options; i++) {
            if (options[i].is_default) default_index = i;
        }

        if (default_index == -1) return options[0];
        else return options[default_index];
    }
}
