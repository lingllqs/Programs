#include <stdio.h>
#include <time.h>
#include <stdlib.h>


#define N 10

void mswap(int *a, int *b)
{
    int tmp = *a;
    *a = *b;
    *b = tmp;
}

void pri(int *arr, int len)
{
    for (int i = 0; i < len; ++i)
        printf("%d ", arr[i]);
    putchar(10);
}

void selectSort(int *arr, int len)
{
    int index;
    for (int i = 0; i < len - 1; ++i)
    {
        index = i;// 保存下标
        for (int j = i + 1; j < len; ++j)// 找最小值
        {
            if (arr[index] > arr[j]) index = j;// 保存当前最小值的下标
        }
        if (index != i) mswap(&arr[index], &arr[i]);// 如果index==i,说明后面的值都比当前值大
    }
}

int main()
{
    srand(time(NULL));
    int arr[N];
    for (int i = 0; i < N; ++i)
        arr[i] = rand() % 20;
    pri(arr, N);
    selectSort(arr, N);
    pri(arr, N);
    return 0;
}
