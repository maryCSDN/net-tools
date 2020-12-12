#ifndef _C_LOG_H
#define _C_LOG_H

#include <zlog.h>
#include <stdarg.h>

extern int _clog_init(void);

#define clog_init() _clog_init()
#define clog_fin() zlog_fin()
#define clog_debug(...) dzlog_debug(__VA_ARGS__)
#define clog_info(...) dzlog_info(__VA_ARGS__)
#define clog_warn(...) dzlog_warn(__VA_ARGS__)
#define clog_error(...) dzlog_error(__VA_ARGS__)

#endif