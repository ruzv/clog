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


// init_logger initialises logger with output stream and configurations settings
// like
// log_file - whether to log the file from what the log call was made.
// log_func - whether to log the function that the log was called from.
// log_level - whether to log the logs level, like ERROR, WARN, INFO, DEBUG.
// log_color - whether to use ASCII escape codes to color the log.
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


// log_error logs the specified arguments with log level - ERROR. log_error
// expects arguments in format log_error(char* fmt, ...)
#define log_error(...) log_all(__FILE__, __LINE__, __FUNCTION__, LOG_LEVEL_ERROR, __VA_ARGS__)
// log_warn logs the specified arguments with log level - WARN. log_error
// expects arguments in format log_warn(char* fmt, ...)
#define log_warn(...) log_all(__FILE__, __LINE__, __FUNCTION__, LOG_LEVEL_WARN, __VA_ARGS__)
// log_info logs the specified arguments with log level - WARN. log_error
// expects arguments in format log_info(char* fmt, ...)
#define log_info(...) log_all(__FILE__, __LINE__, __FUNCTION__, LOG_LEVEL_INFO, __VA_ARGS__)
// log_debug logs the specified arguments with log level - DEBUG. log_error
// expects arguments in format log_debug(char* fmt, ...)
#define log_debug(...) log_all(__FILE__, __LINE__, __FUNCTION__, LOG_LEVEL_DEBUG, __VA_ARGS__)


#endif
