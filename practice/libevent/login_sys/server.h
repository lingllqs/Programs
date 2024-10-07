#ifndef SERVER_H
#define SERVER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <bits/types/struct_timeval.h>
#include <event2/event.h>
#include <event2/listener.h>
#include <event2/bufferevent.h>
#include <event2/buffer.h>
#include <event2/util.h>
#include <hiredis/read.h>
#include <hiredis/hiredis.h>
#include <hiredis/adapters/libevent.h>
#include <hiredis/async.h>


void connectCallback(const redisAsyncContext *c, int status);
void disconnectCallback(const redisAsyncContext *c, int status);
static void on_read(struct bufferevent *bev, void *arg);
static void on_error(struct bufferevent *bev, short events, void *arg);
void on_open(struct evconnlistener *listener, evutil_socket_t fd, struct sockaddr *sock, int socklen, void *arg);

#endif
