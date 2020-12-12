#include "clog.h"

static int net_tools_init(void);

int main(int argc, char **argv)
{
    if (net_tools_init() != 0)
    {
        return -1;
    }

    clog_info("this is zlog <info>.");
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
        printf("Failed to log initialize, [%d].\n", rs);
        return -1;
    }

    return 0;
}