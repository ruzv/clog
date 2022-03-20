#ifndef LOGGING
#define LOGGING


#include <stdio.h>
#include <stdarg.h>
#include <stdbool.h>
#include <time.h>


#define LOG_LEVEL_ERROR 4
#define LOG_LEVEL_WARN 3
#define LOG_LEVEL_INFO 2
#define LOG_LEVEL_DEBUG 1


typedef struct LOGGER {
    FILE* file;
    bool log_file;
    bool log_func;
    bool log_level;
    bool log_color;
} logger;


logger lg;


void init_logger(
    FILE* file,
    bool log_file,
    bool log_func,
    bool log_level,
    bool log_color
);


int log_all(
    const char* file,
    int line,
    const char* func,
    int level,
    const char* fmt,
    ...
);


#define log_error(...) log_all(__FILE__, __LINE__, __FUNCTION__, LOG_LEVEL_ERROR, __VA_ARGS__)
#define log_warn(...) log_all(__FILE__, __LINE__, __FUNCTION__, LOG_LEVEL_WARN, __VA_ARGS__)
#define log_info(...) log_all(__FILE__, __LINE__, __FUNCTION__, LOG_LEVEL_INFO, __VA_ARGS__)
#define log_debug(...) log_all(__FILE__, __LINE__, __FUNCTION__, LOG_LEVEL_DEBUG, __VA_ARGS__)


#endif
