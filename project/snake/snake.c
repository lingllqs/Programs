#include "snake.h"
#include <linux/input-event-codes.h>
#include <linux/input.h>
#include <fcntl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <time.h>
#include <unistd.h>

int ROW = 80;
int COL = 60;

SnakeBody *body_init(Point pos) {
    SnakeBody *snakebody = (SnakeBody *)malloc(sizeof(SnakeBody));
    if (!snakebody) {
        perror("snakebody malloc");
        return NULL;
    }
    snakebody->pos.x = pos.x;
    snakebody->pos.y = pos.y;
    snakebody->prev = NULL;
    snakebody->next = NULL;

    return snakebody;
}

Snake *snake_init() {
    Snake *snake = (Snake *)malloc(sizeof(Snake));
    if (!snake) {
        perror("snake malloc");
        return NULL;
    }

    Point pos1 = {3, 6};
    Point pos2 = {3, 5};
    Point pos3 = {3, 4};
    SnakeBody *snakebody1 = body_init(pos1);
    SnakeBody *snakebody2 = body_init(pos2);
    SnakeBody *snakebody3 = body_init(pos3);

    snake->head = snakebody1;
    snakebody1->next = snakebody2;
    snakebody2->prev = snakebody1;
    snakebody2->next = snakebody3;
    snakebody3->prev = snakebody2;
    snake->tail = snakebody3;

    snake->length = 3;
    snake->direction = Right;
    snake->eat_flag = false;
    snake->status = true;
    return snake;
}

// GameMap* map_init() {
//     GameMap *gamemap = (GameMap *)malloc(sizeof(GameMap));
//     for (int i = 0; i < ROW; ++i) {
//         for (int j = 0; j < COL; ++j) {
//             if (i == 0 || j == 0 || i == ROW - 1 || j == COL - 1) {
//                 gamemap->mapflag[i][j] = Wall;
//             }
//             else {
//                 gamemap->mapflag[i][j] = Space;
//             }
//         }
//     }
//     return gamemap;
// }

void draw_map() {
    struct winsize winsz;
    ioctl(0, TIOCGWINSZ, &winsz);
    ROW = winsz.ws_row;
    COL = winsz.ws_col;
    for (int i = 0; i < ROW; ++i) {
        for (int j = 0; j < COL; ++j) {
            if (i == 0 || j == 0 || i == ROW - 1 || j == COL - 1) {
                printf("\033[34;44m%c\033[0m", ' ');
            }
            else {
                printf("%c", ' ');
            }
        }
        if (i < ROW - 1)
          putchar(10);
    }
}

void draw_snake(Snake *snake) {
    SnakeBody *p = snake->tail;
    for (int i = 0; i < snake->length; ++i) {
        printf("\033[%d;%dH\033[33;43m%c\033[0m", p->pos.x, p->pos.y, ' ');
        p = p->prev;
    }
}

void move_snake(Snake *snake) {
    SnakeBody *p = snake->tail;
    Point pos = {.x = snake->tail->pos.x, .y = snake->tail->pos.y};
    for (int i = 0; i < snake->length - 1; ++i) {
        p->pos.x = p->prev->pos.x;
        p->pos.y = p->prev->pos.y;
        p = p->prev;
    }
    switch (snake->direction) {
        case Up:
            snake->head->pos.x -= 1;
            break;
        case Down:
            snake->head->pos.x += 1;
            break;
        case Left:
            snake->head->pos.y -= 1;
            break;
        case Right:
            snake->head->pos.y += 1;
            break;
        default:
            printf("direction error\n");
            break;
    }
    draw_snake(snake);
    printf("\033[%d;%dH%c", pos.x, pos.y, ' ');
    fflush(stdout);
}

void ctl_snake(Snake *snake) {
  int fd = open("/dev/input/event4", O_RDONLY); 
  if (fd == -1) {
    perror("open");
  }

  struct input_event ev;
  while (1) {
    int ret = read(fd, &ev, sizeof(ev));
    if (ret == -1) {
      perror("read");
    }
    int code = ev.code;
    if (ev.type == EV_KEY && ev.value == 1) {
      switch (code) {
      case 103:
          if (snake->direction != Down) {
            snake->direction = Up;
          }
          break;
      case 108:
          if (snake->direction != Up) {
            snake->direction = Down;
          }
          break;
      case 105:
          if (snake->direction != Right) {
            snake->direction = Left;
          }
          break;
      case 106:
          if (snake->direction != Left) {
            snake->direction = Right;
          }
          break;
      default:
          break;
      }
    }
  }
}
