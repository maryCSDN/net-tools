#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>
#include "clog.h"
#include "server.h"
#include "client.h"

#define ERROR_LOG(format, args...) printf("[%s:%s:%d]"format"\n", __FILE__, __func__, __LINE__, ##args)

static int net_tools_init(void);

int main(int argc, char **argv)
{
    if (net_tools_init() != 0)
    {
        return -1;
    }

    server_start();
    client_start();    
    listen_process();

    return 0;
}

/**
 * All initialize
 */ 
static int net_tools_init(void)
{
    int rs;
    if ( (rs = clog_init()) != 0)
    {
        ERROR_LOG("Failed to log initialize, [%d]", rs);
        return -1;
    }

    return 0;
}