#include <pthread.h>
#include <unistd.h>
#include "broadcast.h"
#include "clog.h"
#include "server.h"

int server_start()
{
    pthread_t tidp;

    if (pthread_create(&tidp, NULL, recv_broadcast, NULL) != 0)
    {
        clog_error("Failed to create pthread!");
        return -1;
    }

    sleep(0);
    return 0;
}


// /* 线程pthread睡眠2s，此时main可以先执行 */
// printf("mian continue!\n");
 
//  /* 等待线程pthread释放 */
//   if (pthread_join(tidp, NULL))                  
//   {
//     printf("thread is not exit...\n");
//  return -2;
// }


int server_stop()
{
    return 0;
}