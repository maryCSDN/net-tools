#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>
#include "clog.h"
#include "broadcast.h"



int send_broadcast(char dv)
{
    int sock = -1;
    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        clog_error("Failed to create socket. [ERRCODE=%d]", sock);
        return -1;
    }

    int optval = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_BROADCAST, (char *)&optval, sizeof(optval)) != 0)
    {
        clog_error("Failed to set socket broadcast option. [EERORCODE=%d]", errno);
        goto _EXCEPT;
    }

    struct sockaddr_in to_addr;
    bzero(&to_addr, sizeof(struct sockaddr_in));
    to_addr.sin_family = AF_INET;
    to_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);
    to_addr.sin_port = htons(BROADCAST_PORT);
    int addr_len = sizeof(to_addr);

    if (sendto(sock, &dv, sizeof(dv), 0, (struct sockaddr *)&to_addr, addr_len) == -1)
    {
        clog_error("Failed to send broadcast.[ERRORCODE=%d]", errno);
        return -1;
    }

    clog_debug("Send broadcast finshed.");
    close(sock);
    return 0;

_EXCEPT:
    if (sock != -1)
    {
        close(sock);
    }
    return -1;
}


void *recv_broadcast(void *args)
{
    int sock = -1;

    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        clog_error("Failed to cretae socket. [ERRORCODE=%d]", errno);
        return NULL;
    }

    /* 设置套接字的属性使它能够在计算机重启的时候可以再次使用套接字的端口和IP */
    int sock_reuse = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&sock_reuse, sizeof(sock_reuse)) != 0)
    {
        clog_error("Failed to set socket reuse option. [ERRORCODE=%d]", errno);
        goto _EXCEPT;
    }

    /* 设置套接字的属性 nonblock */
    struct timeval sock_tv;
    sock_tv.tv_sec = SOCKET_TIMEOUT_SEC;
    sock_tv.tv_usec = SOCKET_TIMEOUT_USEC;
    if (setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, &sock_tv, sizeof(sock_tv)) != 0)
    {
        clog_error("Set broadcast server socket timeout error.");
        return NULL;
    }

    /* Binding socket address */
    struct sockaddr_in my_addr;
    bzero(&my_addr, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(BROADCAST_PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    if (bind(sock, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) != 0)
    {
        clog_error("Failed to bind socket addr. [ERRORCODE=%d]", errno);
        return NULL;
    }

    struct sockaddr_in from_addr;
    bzero(&from_addr, sizeof(from_addr));
    socklen_t len = sizeof(from_addr);
    char buf[16] = {0};
    unsigned int wait_time = 1;
    //static bool init_flag = true;
    while (1)
    {      
        clog_debug("waiting...");
        //读取数据
        if (recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr*) &from_addr, &len) > 0)
        {
            //if (init_flag) {init_flag = false;}
            clog_info("Recv:%d，from ip:%s.", buf[0], inet_ntoa(from_addr.sin_addr));
            bzero(buf, sizeof(buf));
            bzero(&from_addr, sizeof(from_addr));
            wait_time = 1;
        }
        else
        {
            // if (init_flag) {system("sudo iptables -A INPUT -p udp --dport 9999 -j ACCEPT");init_flag = false;}
            clog_debug("Wait time out:%d", errno);

            if (wait_time < 5)
            {
                usleep((wait_time++) * BROADCAST_TIMEOUT_UNIT);
            }
            else
            {
                usleep((wait_time) * BROADCAST_TIMEOUT_UNIT);
            }                       
        }
    }

    close(sock);
    return NULL;

_EXCEPT:
    if (sock != -1)
    {
        close(sock);
    }
    return NULL;
}