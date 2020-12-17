#include <pthread.h>
#include <unistd.h>
#include "broadcast.h"
#include "clog.h"
#include "server.h"

pthread_t server_start()
{
    pthread_t tidp;

    if (pthread_create(&tidp, NULL, recv_broadcast, NULL) != 0)
    {
        clog_error("Failed to create pthread!");
        return -1;
    }

    usleep(BROADCAST_TIMEOUT_UNIT);
    return tidp;
}


int server_stop()
{
    return 0;
}