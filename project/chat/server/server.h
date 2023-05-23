#ifndef SERVER_H
#define SERVER_H

#include <sys/epoll.h>
#include <errno.h>
#include "../socket/socket.h"
#include <ctype.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/socket.h>
#include <stdbool.h>
#include "../../2_线程池/threadpool.h"

#define MAX_EPOLL_EVENTS 1024
#define MAX_CLIENT_NUM 10

typedef struct SocketInfo
{
    int epfd;// epoll实例
    int fd;// 要处理的fd
}SocketInfo;


typedef struct ClientInfo
{
    struct sockaddr_in caddr;
    socklen_t caddrlen;
    int cfd;
}ClientInfo;


void init();
// 创建epoll实例
int createEpoll();
// 设置fd为非阻塞
int setNonBlock(int fd);
// 添加fd到epoll实例上
void addFdToEpoll(int epfd, int fd, bool enable_et);
#endif
