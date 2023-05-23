#include "snake.h"
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>
#include <sys/time.h>


Snake  *snake;

void* func(void *arg)
{
    Snake *s = (Snake *)arg;
    ctl_snake(s);
    return NULL;
}

void handler(int sig)
{
    move_snake(snake);
}
int main (int argc, char *argv[])
{
    snake = snake_init();
    struct itimerval it;
    it.it_interval.tv_sec = 1;
    it.it_interval.tv_usec = 0;
    it.it_value.tv_sec = 1;
    it.it_value.tv_usec = 0;

    setitimer(ITIMER_REAL, &it, NULL);
    signal(SIGALRM, handler);
    system("clear");
    system("stty -echo");
    draw_map();
    draw_snake(snake);

    pthread_t th;
    pthread_create(&th, NULL, func, (void*)snake);
    while (1) sleep(1);
    // ctl_snake(snake);    
    printf("main exit");
    system("stty echo");
    return 0;
}
