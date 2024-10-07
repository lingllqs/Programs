#include "server.h"

ThreadPool *pool;
ClientInfo client[MAX_CLIENT_NUM];

void init()
{
    pool = threadPoolCreate(3, 11, 100);
    for (int i = 0; i < MAX_CLIENT_NUM; ++i)
    {
        client[i].cfd = -1;
    }
}

int createEpoll()
{
    int epfd = epoll_create(1);
    if (epfd == -1)
    {
        perror("epoll_create error");
        return -1;
    }
    return epfd;
}


int setNonBlock(int fd)
{
    int old_flag = fcntl(fd, F_GETFL);
    int new_flag = old_flag | O_NONBLOCK;
    fcntl(fd, F_SETFL, new_flag);
    return old_flag;
}

void addFdToEpoll(int epfd, int fd, bool enable_et)
{
    struct epoll_event event;
    event.data.fd = fd;
    event.events = EPOLLIN;
    if (enable_et)
    {
        event.events |= EPOLLET;
    }
    int ret = epoll_ctl(epfd, EPOLL_CTL_ADD, fd, &event);
    if (ret == -1)
    {
        perror("epoll_ctl error");
    }
}

