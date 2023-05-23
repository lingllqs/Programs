#include <event2/util.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdio.h>
#include <event2/event.h>
#include <sys/socket.h>


int create_listen_fd(const char *ip, short port)
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd == -1)
    {
        printf("%s socket error\n", __func__);
        return -1;
    }

    struct sockaddr_in saddr = {0};
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    evutil_inet_pton(AF_INET, ip, &saddr.sin_addr.s_addr);

    int ret;
    ret = bind(listenfd, (struct sockaddr *)&saddr, sizeof(struct sockaddr_in));
    if (-1 == ret)
    {
        printf("%s bind error\n", __func__);
        close(listenfd);
        return -2;
    }

    ret = listen(listenfd, 10);
    if (ret == -1)
    {
        printf("%s listen error\n", __func__);
        close(listenfd);
        return -3;
    }

    return listenfd;
}

void on_conn(evutil_socket_t fd, short event, void *arg)
{
    struct sockaddr_in caddr = {0};
    socklen_t clen = sizeof(caddr);

    int cfd;
    cfd = accept(fd, (struct sockaddr *)&caddr, &clen);
    if (cfd < 0)
    {
        printf("%s accept error\n", __func__);
        return;
    }

    printf("New Client Connected: %s:%d\n", inet_ntoa(caddr.sin_addr), ntohs(caddr.sin_port));
     
}

int main()
{
    int listenfd = create_listen_fd("127.0.0.1", 10086);
    if (listenfd == -1) 
    {
        printf("%s create_listen_fd error\n", __func__);
    }

    struct event *ev = NULL;
    struct event_base *base = NULL;

    // 创建一个管理器base
    base = event_base_new();
    if (!base)
    {
        printf("%s event_base_new error\n", __func__);
        close(listenfd);
        return -1;
    }

    // 新建一个事件
    // event_self_cbarg函数获取event_new函数的返回值
    // 并将返回值作为参数传递给on_conn函数
    ev = event_new(base, listenfd, EV_READ | EV_PERSIST, on_conn, event_self_cbarg());
    if (!ev)
    {
        printf("%s event_new error\n", __func__);
        event_base_free(base);
        close(listenfd);
        return -2;
    }

    // 将新创建的事件ev添加到等待集合中，在添加之前必须先调用event_new或者通过event_assign指定
    event_add(ev, NULL);

    // 持续分发事件，直到没有更多事件到来或者处于活动状态，或者调用了终止函数
    event_base_dispatch(base);

    // 释放资源
    event_free(ev);
    event_base_free(base);

    return 0;
}
