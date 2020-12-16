#include "client.h"
#include "broadcast.h"

int client_start()
{
    send_broadcast(BV_DEFAULT);
    return 0;
}

int client_stop()
{
    return 0;
}