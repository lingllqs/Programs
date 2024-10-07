#include "imp.h"
#include "server.h"
#include <stdio.h>

redisAsyncContext *redis_conn;

void connectCallback(const redisAsyncContext *c, int status)
{
    if (status != REDIS_OK)
    {
        printf("Connect Redis Error: %s\n", c->errstr);
        return;
    }
    printf("Redis Connected...\n");
}

void disconnectCallback(const redisAsyncContext *c, int status)
{
    if (status != REDIS_OK)
    {
        printf("Connect Redis Error: %s\n", c->errstr);
        return;
    }
    printf("Redis Disconnected...\n");
}

// 读事件处理函数
static void on_read(struct bufferevent *bev, void *arg)
{
    // 获取读缓冲区的信息
    struct evbuffer *evbuf = bufferevent_get_input(bev);
    char *msg = evbuffer_readln(evbuf, NULL, EVBUFFER_EOL_CRLF);
    if (!msg) return;
    /*printf("Server Read the Data: %s\n", msg);*/

    // 解析读到的信息
    struct Arg *args = split_req(msg);
    free(msg);

    // 获取信息中命令部分，判断是否是非法命令
    struct Command *c = get_command(args->str);
    if (!c)
    {
        const char *data = "Invalid Command\n";
        printf("%s", data);
        bufferevent_write(bev, data, strlen(data));
        free_req(args);
        return;
    }
    c->proc(bev, args);

    /*printf("cmd: %s, eles: %ld\n", args->str, args->eles);*/
}

static void on_error(struct bufferevent *bev, short events, void *arg)
{
    if (events & BEV_EVENT_EOF)
        printf("Connection Closed\n");
    else if (events & BEV_EVENT_ERROR)
        printf("Some Other Error\n");
    else if (events & BEV_EVENT_TIMEOUT)
        printf("Timeout\n");
    bufferevent_free(bev);
}

void on_open(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sock, int socklen, void *arg)
{
    char ip[32] = {0};
    evutil_inet_ntop(AF_INET, sock, ip, sizeof(ip) - 1);
    printf("Accept a Client IP: [%s] fd: [%d]\n", ip, fd);

    // 注册事件
    struct event_base *base = (struct event_base *)arg;
    struct bufferevent *bev = bufferevent_socket_new(base, fd, BEV_OPT_CLOSE_ON_FREE);
    // 设置回调函数
    bufferevent_setcb(bev, on_read, NULL, on_error, NULL);
    // 开启检测
    bufferevent_enable(bev, EV_READ | EV_PERSIST);
}


