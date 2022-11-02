#include "common.h"

typedef struct
{
    // configure
    char *filepath;
    int count;
    int size;
    int level;

    int enable_filelog;
    int enable_console_log;
    int enable_syslog;

    pthread_mutex_t logfile_lock;
    FILE *fp;
} _debug_conf_t;

static _debug_conf_t debug_conf = {
    .filepath = NULL,
    .count = 0,
    .size = LOG_FILE_MAX_SIZE,
    .level = LOG_INFO,

    .enable_filelog = 0,
    .enable_console_log = 0,
    .enable_syslog = 0,

    .fp = NULL,
};

void _debug(const char *filename, int line, int level, const char *format, ...)
{
    va_list vlist;
    char buf[28];

    if (level > debug_conf.level)
    {
        return;
    }

    if (debug_conf.enable_console_log || debug_conf.enable_filelog)
    {
        time_t ts = time(NULL);
        struct tm *curtime = localtime(&ts);

        snprintf(buf, sizeof(buf), "%02d-%02d-%02d %02d:%02d:%02d", curtime->tm_year + 1900 - 2000, curtime->tm_mon + 1, curtime->tm_mday, curtime->tm_hour, curtime->tm_min, curtime->tm_sec);
    }

    if (debug_conf.enable_console_log)
    {
        fprintf(stderr, "[%d][%s](%s:%d) ", level, buf, filename, line);
        va_start(vlist, format);
        vfprintf(stderr, format, vlist);
        va_end(vlist);
        fputc('\n', stderr);
    }

    if (debug_conf.enable_syslog)
    {
        va_start(vlist, format);
        vsyslog(level, format, vlist);
        va_end(vlist);
    }

    if (debug_conf.enable_filelog)
    {
        static size_t size = 0;
        int retval = 0;

        pthread_mutex_lock(&debug_conf.logfile_lock);

        if (NULL == debug_conf.fp)
        {
            struct stat statbuf;
            if (0 == stat(debug_conf.filepath, &statbuf))
            {
                size = statbuf.st_size;
            }
            else
            {
                size = 0;
            }

            debug_conf.fp = fopen(debug_conf.filepath, "a");
        }

        if (debug_conf.fp)
        {
            fprintf(debug_conf.fp, "[%d][%s](%s:%d) ", level, buf, filename, line);
            va_start(vlist, format);
            retval = vfprintf(debug_conf.fp, format, vlist);
            if (retval >= 0)
            {
                size += retval;
            }
            va_end(vlist);
            fputc('\n', debug_conf.fp);
            fflush(debug_conf.fp);
            size += 1;

            if (size >= debug_conf.size)
            {
                char backup_filepath[128] = {0};

                safe_fclose(debug_conf.fp);

                buf[2] = buf[5] = buf[8] = buf[11] = buf[14] = '_';
                snprintf(backup_filepath, sizeof(backup_filepath), "%s.%s", debug_conf.filepath, buf);
                rename(debug_conf.filepath, backup_filepath);
            }
        }

        pthread_mutex_unlock(&debug_conf.logfile_lock);
    }
}

int init_debug(int console, const char *filepath, int count, int size, int level, const char *ident)
{
    pthread_mutex_init(&debug_conf.logfile_lock, NULL);

    if (filepath)
    {
        debug_conf.filepath = strdup(filepath);
        debug_conf.enable_filelog = 1;
    }
    else
    {
        safe_free(debug_conf.filepath);
        debug_conf.enable_filelog = 0;
    }
    debug_conf.count = count;
    debug_conf.size = size;
    debug_conf.level = level;
    debug_conf.enable_console_log = console;

    if (ident)
    {
        debug_conf.enable_syslog = 1;
        openlog(ident, LOG_CONS, LOG_USER);
    }
    else
    {
        debug_conf.enable_syslog = 0;
        closelog();
    }

    return 0;
}
