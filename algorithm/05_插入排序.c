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

void insertSort(int *arr, int len)
{
    for (int i = 1; i < len; ++i) {// 从数组中取一个数与前面的比较
        for (int j = i; j > 0; j--) {// 前面有多少个数，最大比较次数将组成多少
            if (arr[j] < arr[j - 1]) {// 从小到大排序
                mswap(&arr[j], &arr[j - 1]);
            } else {
                break;// 从小到大排序，所以当前数大于前面所有数，不用比较
            }
        }
    }
}

int main()
{
    srand(time(NULL));
    int arr[N];
    for (int i = 0; i < N; ++i)
        arr[i] = rand() % 20;
    pri(arr, N);
    insertSort(arr, N);
    pri(arr, N);
    return 0;
}
