#ifndef _DEBUG_H_
#define _DEBUG_H_

extern void _debug(const char *filename, int line, int level, const char *format, ...);
extern int init_debug(int console, const char *filepath, int count, int size, int level, const char *ident);

#define filename(x) (strrchr(x, '/') ? strrchr(x, '/') + 1 : x)

#define log_noisy(format...) _debug(filename(__FILE__), __LINE__, LOG_ALL, format)
#define log_debug(format...) _debug(filename(__FILE__), __LINE__, LOG_DEBUG, format)
#define log_info(format...) _debug(filename(__FILE__), __LINE__, LOG_INFO, format)
#define log_notice(format...) _debug(filename(__FILE__), __LINE__, LOG_NOTICE, format)
#define log_warn(format...) _debug(filename(__FILE__), __LINE__, LOG_WARNING, format)
#define log_error(format...) _debug(filename(__FILE__), __LINE__, LOG_ERR, format)
#define log_crit(format...) _debug(filename(__FILE__), __LINE__, LOG_CRIT, format)
#define log_alert(format...) _debug(filename(__FILE__), __LINE__, LOG_ALERT, format)
#define log_emerg(format...) _debug(filename(__FILE__), __LINE__, LOG_EMERG, format)

#endif
