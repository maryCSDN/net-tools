#include <signal.h>
#include "clog.h"
#include "utils.h"
#include "cml.h"

static int net_tools_init(void);

int main(int argc, char **argv)
{
    signal(SIGCHLD, SIG_IGN);

    if (net_tools_init() != 0)
    {
        CONSOLE_LOG("Cnet tools initializal error.");
        return -1;
    }

    return nettools_cml(argc, argv);
}

/**
 * All initialize
 */ 
static int net_tools_init(void)
{
    int rs;
    if ( (rs = clog_init()) != 0)
    {
        CONSOLE_LOG("Failed to log initialize, [%d]", rs);
        return -1;
    }

    return 0;
}