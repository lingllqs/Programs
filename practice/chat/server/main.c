#include <stdio.h>
#include "server.h"


int main()
{
    init();
    int fd = createSocket();
    bindServer(fd, NULL, 10000);
    setListen(fd);
    return 0;
}

