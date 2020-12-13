#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <errno.h>
#include <strings.h>
#include <unistd.h>
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

    int i = 5;
    char data[] = {0x01, 0x02, 0x03, 0x04, 0x05}; 
    while(i > 0 && i--)
    {
        sleep(1);
        if(sendto(sock, data, sizeof(data), 0, (struct sockaddr*)&to_addr, addr_len) == -1)
        {
            clog_error("Failed to send broadcast.[ERRORCODE=%d]", errno);
            break;
        }
        clog_debug("Send broadcast. [%d]", i);
    }

    clog_info("Broadcast finished.");
    close(sock);
    return 0;

_EXCEPT:
    if (sock != -1)
    {
        close(sock);
    }
    return -1;
}


int recv_broadcast()
{
    int sock = -1;

    if ((sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
    {
        clog_error("Failed to cretae socket. [ERRORCODE=%d]", errno);
        return -1;
    }

    //设置套接字的属性使它能够在计算机重启的时候可以再次使用套接字的端口和IP
    int sock_reuse = 1;
    if (setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, (char *)&sock_reuse, sizeof(sock_reuse)) != 0)
    {
        clog_error("Failed to set socket reuse option. [ERRORCODE=%d]", errno);
        goto _EXCEPT;
    }

    struct sockaddr_in my_addr;
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(BROADCAST_PORT);
    my_addr.sin_addr.s_addr = INADDR_ANY;
    bzero(&(my_addr.sin_zero), 8);

    if (bind(sock, (struct sockaddr *)&my_addr, sizeof(struct sockaddr)) != 0)
    {
        clog_error("Failed to bind socket addr. [ERRORCODE=%d]", errno);
        return -1;
    }

    struct sockaddr_in from_addr;
    socklen_t len = sizeof(from_addr);
    char buf[1024] = {0};
    while (1)
    {
        //读取数据
        if (recvfrom(sock, buf, sizeof(buf) - 1, 0, (struct sockaddr*) &from_addr, &len))
        {
            clog_info("Recv:%s，from ip:%s.", buf, inet_ntoa(from_addr.sin_addr));
        }
    }

    close(sock);
    return 0;

_EXCEPT:
    if (sock != -1)
    {
        close(sock);
    }
    return -1;
}