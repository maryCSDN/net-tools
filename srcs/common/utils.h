#ifndef __NET_TOOLS_UTILS_H
#define __NET_TOOLS_UTILS_H

#include <stdbool.h>
#include <stdarg.h>
#include <stdio.h>
#include <zlog.h>

typedef enum _process_status_value
{
    PSV_EXIT = 0,
#define _PSV_EXIT        PSV_EXIT
    PSV_ACTIVE,
#define _PSV_ACTIVE      PSV_ACTIVE
    PSV_EXCEPT,
#define _PSV_EXCEPT      PSV_EXCEPT
    PSV_SLEEP,
#define _PSV_SLEEP       PSV_SLEEP
    PSV_BORDER, /* invalid value */
#define _PSV_BORDER      PSV_BORDER
}psv_t;


/**
 * console log
 */
#define CONSOLE_LOG(format, args...) printf("[%s:%s:%d]"format"\n", __FILE__, __func__, __LINE__, ##args)

/**
 * clog -> zlog
 */ 
extern int _clog_init(void);
#define clog_init() _clog_init()
#define clog_fin() zlog_fin()
#define clog_debug(...) dzlog_debug(__VA_ARGS__)
#define clog_info(...) dzlog_info(__VA_ARGS__)
#define clog_warn(...) dzlog_warn(__VA_ARGS__)
#define clog_error(...) dzlog_error(__VA_ARGS__)

/**
 * process check
 * psv: process statue value
 */ 
extern bool is_active(psv_t psv);
extern bool is_except(psv_t psv);
extern bool is_sleep(psv_t psv);
extern bool is_exit(psv_t psv);
extern bool is_online(void);
extern psv_t set_psv(psv_t psv);
extern psv_t get_psv(void);
extern char *to_psvstring(psv_t psv);
#endif