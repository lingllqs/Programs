#ifndef SOCKET_H
#define SOCKET_H

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>



// 创建套接字
int createSocket();
// 绑定服务器
int bindServer(int fd, const char *ip, unsigned short port);
// 设置监听
int setListen(int listenfd);
// 连接服务器
int connServer(int fd, const char *ip, unsigned short port);
// 发送数据流
int sendByte(int fd, const char *msg, int size);
// 自定义数据包发送
int sendMsg(int fd, const char *msg, int len);
// 接受数据流
int recvByte(int fd, char *msg, int size);
// 自定义数据包接收
int recvMsg(int fd, char **buf);


#endif 
