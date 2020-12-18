#ifndef __BROADCAST_H
#define __BROADCAST_H

/* Broadcast socket timeout */
#define BROADCAST_TIMEOUT_UNIT  (1000)  /* (us) */
#define SOCKET_TIMEOUT_SEC      (0x00)  /* (s)  */
#define SOCKET_TIMEOUT_USEC     BROADCAST_TIMEOUT_UNIT  /* (us) */
/* Broadcast server configure */
#define BROADCAST_PORT          (9999)  /* 默认的接收广播端口 */
/* Broadcast value */
#define BV_GET_HOSTINFO         (0x01)  /* 获取主机信息 */
#define BV_DEFAULT              BV_GET_HOSTINFO /* 广播默认数据 */



extern int send_broadcast(char dv);
extern void * recv_broadcast(void *args);

#endif