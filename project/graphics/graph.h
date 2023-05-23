#ifndef GRAPH_H
#define GRAPH_H

typedef struct Point_t {
    int x;
    int y;
} Point;

typedef struct Size_t {
    int width;
    int height;
} Size;

void draw_rect(Point point, Size size, char ch);

#endif /* !GRAPH_H                                                             \
defi */
