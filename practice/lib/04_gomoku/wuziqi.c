#include <stdio.h>

#define ROWS 15
#define COLS ROWS

enum
{
    EMPTY,
    WHITE,
    BLACK
};

const char chess_char[] = {'+', 'o', '#'};

int chess_data[ROWS][COLS];

void show_chess_data(int data)
{
    printf("%c  ", chess_char[data]);
}

void show_board()
{
    printf("  ");
    for (int i = 0; i < COLS; i++)
        printf("%3d", i + 1);
    printf("\n");

    for (int i = 0; i < ROWS; i++)
    {
        printf("%-3d ", i + 1);
        for (int j = 0; j < COLS; j++)
        {
            show_chess_data(chess_data[i][j]);
        }
        printf("\n");
    }
}

int put_chess(int x, int y, int role)
{
    if (chess_data[x - 1][y - 1] == EMPTY)
    {
        chess_data[x - 1][y - 1] = role;
        return 0;
    }
    return -1;
}

int win(int x, int y, int role)
{
    int left_count = 0, right_count = 0;
    int y1 = y - 1;
    while (y1-- && chess_data[x - 1][y1] == role)
    {
        left_count++;
    }
    int y2 = y - 1;
    while (y2++ < COLS - 1 && chess_data[x - 1][y2] == role)
    {
        right_count++;
    }
    if (left_count + right_count >= 4 && chess_data[x - 1][y - 1] == role)
    {
        return 1;
    }
    return 0;
}

int main(void)
{
    int role = BLACK;
    do
    {
        int x, y;
        show_board();
        printf("%s please put chess(x,y)\n", role == BLACK ? "BLACK" : "WHITE");
        scanf("%d,%d", &x, &y);
        int ret = put_chess(x, y, role);
        if (ret == 0)
        {
            ret = win(x, y, role);
            if (ret == 1)
                break;
            role = (role == BLACK ? WHITE : BLACK);
        }
    } while (1);

    show_board();
    printf("Game over\n");

    return 0;
}
