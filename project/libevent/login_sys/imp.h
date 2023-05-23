#ifndef IMP_H
#define IMP_H

#include <event2/bufferevent.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <hiredis/hiredis.h>
#include <hiredis/async.h>

// 
typedef struct Arg {
    size_t len;
    char *str;
    size_t eles;
    struct Arg *next;
} Arg;

typedef void (*CommandProc)(struct bufferevent *, struct Arg *) ;

typedef struct Command 
{
    char *name;
    CommandProc proc;
    char *desc;
} Command;

struct Arg* split_req(char *msg);
void free_req(struct Arg *);
struct Command* get_command(const char *cmd);

static void reply_error(struct bufferevent *bev, const char *errstr);
void redis_login_hget(struct redisAsyncContext *c, void *r, void *privdata);
void on_login(struct bufferevent *bev, struct Arg *args);
void on_heartbeat(struct bufferevent *bev, struct Arg *args);

#endif
