#ifndef _C_LOG_H
#define _C_LOG_H

#include <zlog.h>
#include <stdarg.h>

extern int _clog_init(void);

#define clog_init() _clog_init()
#define clog_fin() zlog_fin()
#define clog_debug(__ARGS...) dzlog_debug(##__ARGS)
#define clog_info(__ARGS...) dzlog_info(##__ARGS)
#define clog_warn(__ARGS...) dzlog_warn(##__ARGS)
#define clog_error(__ARGS...) dzlog_error(##__ARGS)

#endif