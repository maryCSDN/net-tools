#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include "clog.h"
#include "constant.h"
#include "utils.h"
#include "server.h"
#include "client.h"

static int net_tools_init(void);

int main(int argc, char **argv)
{
    signal(SIGCHLD, SIG_IGN);

    if (is_online())
    {
        int psv = get_psv();
        CONSOLE_LOG("Status:[%s]", psv < 0 ? _PSV_EXCEPT_STRING: to_psvstring(psv));
        // todo exit process
        return 0;
    }

    if (net_tools_init() != 0)
    {
        return -1;
    }

    pthread_t pid = server_start();
    if (pid < 1)
    {
        clog_error("Server error.");
        return -1;
    }

    client_start();
    set_psv(_PSV_ACTIVE);
    pthread_join(pid, NULL);

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
        CONSOLE_LOG("Failed to log initialize, [%d]", rs);
        return -1;
    }

    return 0;
}