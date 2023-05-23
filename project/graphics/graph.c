#include "graph.h"
#include <stdio.h>

void draw_rect(Point point, Size size, char ch)
{
    for (int i = 0; i < size.height; i++) {
        for (int j = 0; j < size.width; j++) {
            if (i == 0 || i == size.height - 1 || j == 0 || j == size.width - 1) {
                printf("\033[%d;%dH\033[37;47m%c\033[0m", point.x + j, point.y + i, ch);
            }
        }
        // putchar(10);
    }
}
