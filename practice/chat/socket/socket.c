#include "socket.h"

int createSocket()
{
    int lfd = socket(AF_INET, SOCK_STREAM, 0);
    if (lfd == -1)
    {
        perror("socket error");
        return -1;
    }
    printf("创建套接字成功!\n");
    return lfd;
}

int bindServer(int fd, const char *ip, unsigned short port)
{
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port); 

    if (ip != NULL) 
    {
        inet_pton(AF_INET, ip, &serverAddr.sin_addr.s_addr);
    }
    else 
    {
        serverAddr.sin_addr.s_addr = INADDR_ANY;
    }
    int ret = bind(fd, (struct sockaddr*)&serverAddr, sizeof(serverAddr));
    if (ret == -1)
    {
        perror("bind error");
        return -1;
    }
    printf("绑定服务器ip和端口成功!\n");
    return 0;
}

int setListen(int listenfd)
{
    int ret = listen(listenfd, 5);
    if (ret == -1)
    {
        perror("listen error");
        return -1;
    }
    printf("设置监听成功!\n");
    return 0;
}

int connServer(int fd, const char *ip, unsigned short port)
{
    struct sockaddr_in saddr;
    saddr.sin_family = AF_INET;
    saddr.sin_port = htons(port);
    inet_pton(AF_INET, ip, &saddr.sin_addr.s_addr);
    int ret = connect(fd, (struct sockaddr*)&saddr, sizeof(saddr));
    if (ret == -1)
    {
        perror("connect error");
        return -1;
    }
    printf("连接服务器成功!\n");
    return 0;
}

int sendByte(int fd, const char *msg, int size)
{
    int count = size;
    const char *buf = msg;
    while (count > 0)
    {
        int len = send(fd, buf, count, 0);
        if (len == -1)
        {
            perror("send");
            close(fd);
            return -1;
        }
        else if (len == 0)
        {
            continue;
        }
        else 
        {
            buf += len;
            count -= len;
        }
    }
    return size;
}

int sendMsg(int fd, const char *msg, int len)
{
    if (fd < 0 || msg == NULL || len <= 0)
    {
        return -1;
    }
    // 组织数据包, 前四个字节为数据包长度len
    char *data = (char *)malloc(len + 4);
    int netlen = htonl(len);
    memcpy(data, &netlen, 4);
    memcpy(data + 4, msg, len);
    int ret = sendByte(fd, data, len + 4);
    if (ret == -1)
    {
        printf("sendByte failure\n");
    }
    free(data);
    return ret;
}

int recvByte(int fd, char *msg, int size)
{
    int count = size;// 记录剩余未接收字节数
    char *buf = msg;
    while (count > 0)
    {
        int len = recv(fd, buf, count, 0);
        if (len == -1)
        {
            close(fd);
            return -1;
        }
        else if (len == 0)
        {
            return size - count;
        }
        else
        {
            buf += len;
            count -= len;
        }
    }
    return size;
}

int recvMsg(int fd, char **buf)
{
    if (fd < 0 || buf == NULL)
    {
        return -1;
    }
    int len;
    recvByte(fd, (char *)&len, sizeof(int));
    len = ntohl(len);

    char *msg = (char *)malloc(len + 1);
    int ret = recvByte(fd, msg, len);
    if (ret != len)
    {
        close(fd);
        free(msg);
        return -1;
    }
    msg[len] = '\0';
    *buf = msg;
    return ret;
}
