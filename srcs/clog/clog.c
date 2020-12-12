#include "clog.h"

#define _LOG_CONF_FILE          "/etc/net-tools/clog.conf"
#define _LOG_RULES_DEFAULT      "net-tools-default"

int _clog_init(void);

int _clog_init(void)
{
    return dzlog_init(_LOG_CONF_FILE, _LOG_RULES_DEFAULT);    
}