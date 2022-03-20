#include "log.h"


// colors
char* file_color = "\x1b[38;5;28m";
char* error_color = "\x1b[31m";
char* warn_color = "\x1b[33m";
char* info_color = "\x1b[32m";
char* debug_color = "\x1b[94m";
char* func_color = "\x1b[38;5;163m";

char* reset_color = "\x1b[0m";


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
) {
    lg.file = file;
    lg.log_file = log_file;
    lg.log_func = log_func;
    lg.log_level = log_level;
    lg.log_color = log_color;
}


// log_all is not intended for external use. generates a single log line with
// the settings specified and writes it to file specified in logger settings.
int log_all(
    const char* file,
    int line,
    const char* func,
    int level,
    const char* fmt,
    ...
) {
    if (lg.file == NULL) {
        fputs("error: can not log with uninitialized logger\n", stderr);

        return 1;
    }

    if (lg.log_file) {
        if (lg.log_color) {
            fprintf(lg.file, "%s%s:%d%s ", file_color, file, line, reset_color);
        } else {
            fprintf(lg.file, "%s:%d ", file, line);
        }
    }

    if (lg.log_level) {
        if (level == LOG_LEVEL_DEBUG) {
            if (lg.log_color) {
                fprintf(lg.file, "%s[DEBUG]%s ", debug_color, reset_color);
            } else {
                fprintf(lg.file, "[DEBUG] ");
            }
        } else if (level == LOG_LEVEL_INFO) {
            if (lg.log_color) {
                fprintf(lg.file, "%s[INFO]%s ", info_color, reset_color);
            } else {
                fprintf(lg.file, "[INFO] ");
            }
        } else if (level == LOG_LEVEL_WARN) {
            if (lg.log_color) {
                fprintf(lg.file, "%s[WARN]%s ", warn_color, reset_color);
            } else {
                fprintf(lg.file, "[WARN] ");
            }
        } else if (level == LOG_LEVEL_ERROR) {
            if (lg.log_color) {
                fprintf(lg.file, "%s[ERROR]%s ", error_color, reset_color);
            } else {
                fprintf(lg.file, "[ERROR] ");
            }
        }
    }

    if (lg.log_func) {
        if (lg.log_color) {
            fprintf(lg.file, "%s%s:%s ", func_color, func, reset_color);
        } else {
            fprintf(lg.file, "%s: ", func);
        }
    }

    va_list ap;
    va_start(ap, fmt);
    vfprintf(lg.file, fmt, ap);
    va_end(ap);

    putc('\n', lg.file);

    fflush(lg.file);

    return 0;
}
