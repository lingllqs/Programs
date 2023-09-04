#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 15

void countSort(int *arr, int range, int len)
{
    int count[range]; //
    memset(count, 0, sizeof(count));
    for (int i = 0; i < len; i++)
    {
        count[arr[i]]++;
    }

    for (int i = 0; i < range; i++)
    {
        while (count[i]-- > 0)
        {
            printf("%d ", i);
        }
    }
    putchar(10);
}

int main()
{
    srand(time(NULL));
    int arr[N];
    for (int i = 0; i < N; ++i)
        arr[i] = rand() % 10;

    for (int i = 0; i < N; ++i)
    {
        printf("%d ", arr[i]);
    }
    putchar(10);

    countSort(arr, 10, N);
    return 0;
}
