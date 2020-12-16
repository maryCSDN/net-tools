
#include "broadcast.h"
#include "server.h"

int server_start()
{
    recv_broadcast();
    return 0;
}

int server_stop()
{
    return 0;
}