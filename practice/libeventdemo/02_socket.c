#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>

#include <event2/event.h>
#include <event2/util.h>

int create_listenfd(const char *ip, short port)
{
    int listenfd = -1;
    int ret;
    listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd < 0)
    {
        return -1;
    }

    struct sockaddr_in localAddr = {0};
    localAddr.sin_family = AF_INET;
    localAddr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &localAddr.sin_addr.s_addr);

    ret = bind(listenfd, (struct sockaddr *)&localAddr, sizeof(localAddr));
    if (ret < 0)
    {
        close(listenfd);
        return -1;
    }

    listen(listenfd, 64);
    return listenfd;
}

void tcp_conn_req_cb(evutil_socket_t fd, short event, void *arg)
{
    printf("fd is %d\n", fd);

    struct sockaddr_in clientAddr;
    socklen_t len = sizeof(clientAddr);
    int clientFd;
    clientFd = accept(fd, (struct sockaddr *)&clientFd, &len);
    if (clientFd < 0)
    {
        return;
    }
    printf("New client is [%s:%d] connected...\n", inet_ntoa(clientAddr.sin_addr), ntohs(clientAddr.sin_port));
}

int main(int argc, char *argv[])
{
    struct event_base *base = NULL;
    int listenFd = -1;
    struct event *eventConnReq;


    listenFd = create_listenfd("127.0.0.1", 12345);
    if (listenFd < 0)
    {
        return -1;
    }

    base = event_base_new();
    if (!base)
    {
        close(listenFd);
        return 0;
    }

    eventConnReq = event_new(base, listenFd, EV_READ | EV_PERSIST, tcp_conn_req_cb, event_self_cbarg());
    if (!eventConnReq)
    {
        close(listenFd);
        event_base_free(base);
        return 0;
    }

    event_add(eventConnReq, NULL);
    event_base_dispatch(base);

    event_base_free(base);

    return EXIT_SUCCESS;
}
