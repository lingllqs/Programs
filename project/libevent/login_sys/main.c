#include "imp.h"
#include "server.h"

extern redisAsyncContext *redis_conn;

int main()
{
    // 创建一个事件管理器的对象
    struct event_base *base = event_base_new();

    struct sockaddr_in sin;
    memset(&sin, 0, sizeof(struct sockaddr_in));
    sin.sin_family = AF_INET;
    sin.sin_port = htons(8989);

    // 设置监听
    struct evconnlistener *listener = evconnlistener_new_bind(base, on_open, base, LEV_OPT_REUSEABLE | LEV_OPT_CLOSE_ON_FREE, 512, (struct sockaddr*)&sin, sizeof(struct sockaddr_in));

    /*printf("server listen port: %d\n", ntohs(sin.sin_port));*/

    // 连接Redis
    redisOptions options = {0};
    REDIS_OPTIONS_SET_TCP(&options, "127.0.0.1", 6379);
    struct timeval tv = {0};
    tv.tv_sec = 1;
    options.connect_timeout = &tv;

    redis_conn = redisAsyncConnectWithOptions(&options);
    if (redis_conn->err)
    {
        printf("Error: %s\n", redis_conn->errstr);
        return 1;
    }

    redisLibeventAttach(redis_conn, base);
    redisAsyncSetConnectCallback(redis_conn, connectCallback);
    redisAsyncSetDisconnectCallback(redis_conn, disconnectCallback);

    // 分发事件
    event_base_dispatch(base);

    //
    event_base_free(base);
    return 0;
}
