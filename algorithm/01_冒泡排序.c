#include <stdio.h>
#include <stdlib.h>
#include <time.h>


void bubblesort(int arr[], int len)
{
    for (int i = 1; i < len; ++i)// 比较次数
    {
        for (int j = 0; j < len -i; j++)// 每一遍比较的次数 
        {
            if (arr[j] > arr[j+1]) {
                int tmp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = tmp;
            }
        }
    }
}

int main(int argc, char *argv[])
{
    srand(time(NULL));
    int arr[10];
    for (int i = 0; i < 10; i++)
    {
      arr[i] = rand() % 10;
    }
    for (int i = 0; i < 10; ++i)
    {
        printf("%d ", arr[i]);
    }
    putchar(10);

    bubblesort(arr, 10);
    for (int i = 0; i < 10; ++i)
    {
        printf("%d ", arr[i]);
    }
    return 0;
}
