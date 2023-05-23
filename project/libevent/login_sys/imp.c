#include "imp.h"
#include <hiredis/async.h>

typedef struct ReplyContext
{
    struct bufferevent *bev;
    struct Arg *args;
} ReplyContext;

extern redisAsyncContext *redis_conn;

struct Command commandTable[] = {
    {"login", on_login, "login: please provide name and password"},
    {"heart", on_heartbeat, "heart: heart beat"}
};

struct Arg* split_req(char *msg)
{
    // 找第一个非空字符
    char *temp = strtok(msg, " ");
    if (!temp) return NULL;
    // 定义一个链表
    struct Arg *req = (struct Arg *)malloc(sizeof(*req));
    if (!req) return NULL;
    req->len = strlen(temp);
    req->str = (char *)malloc(req->len + 1);
    if (!req->str) return NULL;
    memset(req->str, 0, req->len + 1);
    memcpy(req->str, temp, req->len);
    req->eles = 0;
    // 解析是否有参数，有则插入链表中
    struct Arg *tail = req;
    while ((temp = strtok(NULL, " ")))// temp指向下一个非空字符
    {
        struct Arg *ele = (struct Arg *)malloc(sizeof(*ele));
        if (!ele) return NULL;
        ele->len = strlen(temp);
        ele->str = (char *)malloc(ele->len+1);
        if (!ele->str) return NULL;
        memset(ele->str, 0, ele->len+1);
        memcpy(ele->str, temp, req->len);
        tail->next = ele;
        ele->next = NULL;
        tail = ele;
        req->eles++;
    }
    // 返回解析msg后的到的链表
    return  req;
}

// 释放资源
void free_req(struct Arg *args)
{
    int i;
    if (args->eles > 0)
    {
        struct Arg *p = args->next;
        while (p)
        {
            free(p->str);
            struct Arg *t = p;
            p = p->next;
            free(t);
        }
    }
    free(args->str);
    free(args);
}

struct Command* get_command(const char *cmd)
{
    int j;
    // 获取全局变量commandTable中已定义的命令个数
    int numcommands = sizeof(commandTable)/sizeof(struct Command);
    for (j = 0; j < numcommands; ++j)
    {
        struct Command *c = commandTable + j;
        // 在commandTable中匹配，符合则返回
        if (strcmp(cmd, c->name) == 0)
        {
            return c;
        }
    }
    // commandTable中没有匹配到则返回NULL
    return NULL;
}

static void reply_error(struct bufferevent *bev, const char *errstr)
{
    /*printf("%s\n", errstr);*/
    bufferevent_write(bev, errstr, strlen(errstr));
}

void redis_login_hget(struct redisAsyncContext *c, void *r, void *privdata)
{
    // 获取Redis回复的信息
    redisReply *reply = (redisReply *)r;
    /*printf("redis_login_hget: %d\n", reply->type);*/
    struct ReplyContext *rc = (struct ReplyContext *)privdata;
    // 判断Redis回复信息，没有则注册，有则登录
    if (reply->elements == 0)
    {
        struct Arg *temp = rc->args->next;
        const char *name = temp->str;
        temp = temp->next;
        const char *password = temp->str;
        redisAsyncCommand(redis_conn, NULL, NULL, "hmset role:%s name: %s password: %s", name, name, password);
        // 将注册结果发送给服务器
        const char *suc = "Register Success\n";
        bufferevent_write(rc->bev, suc, strlen(suc));
    }
    else 
    {
        const char *suc = "Login Success\n";
        bufferevent_write(rc->bev, suc, strlen(suc));
    }
    free(rc->args);
    free(rc);
}

void on_login(struct bufferevent *bev, struct Arg *args)
{
    /*printf("on_login\n");*/
    if (args->eles < 2) 
    {
        reply_error(bev, "on_login: number of element is wrong");
        return;
    }
    // 提取用户名和密码
    struct Arg *params = args->next;
    const char *name = params->str;
    size_t name_len = params->len;
    params = params->next;
    const char *password = params->str;
    size_t password_len = params->len;


    struct ReplyContext *rc = (struct ReplyContext *)malloc(sizeof(*rc));
    rc->bev = bev;
    rc->args = args;
    // 查询Redis中name项
    redisAsyncCommand(redis_conn, redis_login_hget, rc, "hgetall role:%s", name);

    /*printf("name: %s passwd: %s\n", name, password);*/
}

void on_heartbeat(struct bufferevent *bev, struct Arg *args)
{
    printf("on_heartbeat\n");
}

