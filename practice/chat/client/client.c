#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <arpa/inet.h>


int main(void)
{
    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {
        perror("socket");
        exit(0);
    }


    // 绑定服务器地址和端口
    struct sockaddr_in seraddr;
    seraddr.sin_family = AF_INET;
    seraddr.sin_port = htons(10000);
    /* seraddr.sin_addr.s_addr = INADDR_ANY; */
    inet_pton(AF_INET, "127.0.0.1", &seraddr.sin_addr.s_addr);
    /* bind(fd, (struct sockaddr*)&seraddr, sizeof(seraddr)); */

    // 连接服务器
    int ret = connect(fd, (struct sockaddr*)&seraddr, sizeof(seraddr));
    if (ret == -1)
    {
        perror("connect");
        exit(0);
    }

    while (1)
    {
        char buf[1024];
        memset(buf, 0, sizeof(buf));
        printf("输入要发送的信息: ");
        fgets(buf, sizeof(buf), stdin);
        if (buf[strlen(buf) - 1] == '\n')
        {
            buf[strlen(buf) - 1] = '\0';
        }
        send(fd, buf, sizeof(buf), 0);
        printf("before send: %s\n", buf);
        memset(buf, 0, sizeof(buf));
        int len = recv(fd, buf, sizeof(buf), 0);
        if (len == -1)
        {
            perror("recv");
            exit(0);
        }
        else if (len == 0)
        {
            printf("服务器断开了连接\n");
            close(fd);
            exit(0);
        }
        else
        {
            printf("from server: %s\n", buf);
        }
    }
    return 0;
}
