#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>

#include "utils.h"
#include "constant.h"
#include "server.h"
#include "client.h"
#include "netops.h"


int cheat(void)
{
    if (is_online())
    {
        int psv = get_psv();
        CONSOLE_LOG("Status:[%s]", psv < 0 ? _PSV_EXCEPT_STRING: to_psvstring(psv));
        // todo exit process
        return 0;
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