#ifndef SNAKE_H
#define SNAKE_H

#include "../5_图形库/graph.h"
#include <bits/types/timer_t.h>
#include <stdbool.h>
#include <sys/time.h>
#include <sys/ioctl.h>


typedef enum Direction {
    Up,
    Down,
    Left,
    Right
}Direction;

typedef enum MapFlag {
    Space,
    Wall
}MapFlag;

typedef struct SnakeBody
{
    Point pos;
    struct SnakeBody *prev;
    struct SnakeBody *next;
}SnakeBody;

typedef struct Snake
{
    struct SnakeBody *head;// 蛇头
    struct SnakeBody *tail;// 蛇尾
    int length;// 蛇的长度
    Direction direction;// 蛇的方向
    bool eat_flag;// 吃到食物标志
    bool status;// 蛇的状态
}Snake;

// // 定时器
// typedef void (FUNC)(void *);
// typedef struct Timer
// {
//     int start_time;// 开始时间
//     int count_time;// 累加时间
//     void *data;// 数据
//     FUNC *task_func;// 定时任务
//     int inter_flag;// 循环标志
//     struct my_timer_t *prev;
//     struct my_timer_t *next;
// }Timer;

// void timer_init(void);


SnakeBody* body_init(Point pos);
Snake* snake_init();
void draw_map();
void draw_snake(Snake *snake);
void move_snake(Snake *snake);
void ctl_snake(Snake *snake);



#endif // !DEBUG

