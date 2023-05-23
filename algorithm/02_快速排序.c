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

void quickSort(int *arr, int l, int r)
{
    if (l > r) return;
    int left = l;
    int right = r;
    int base = arr[left];
    while (left < right)
    {
        while (arr[right] >= base && left < right) right--;// 找比base小的值
        while (arr[left] <= base && left < right) left++;// 找比bise大的值
        if (left < right) {
            mswap(&arr[left], &arr[right]);
        }
    }
    mswap(&arr[l], &arr[left]);// 此时的arr[left] <= arr[l], 把base放在这个位置
    quickSort(arr, l, left - 1);
    quickSort(arr, left + 1, r);
}

int main()
{
    srand(time(NULL));
    int arr[N];
    for (int i = 0; i < N; ++i)
        arr[i] = rand() % 10;
    pri(arr, N);
    quickSort(arr, 0, N - 1);
    pri(arr, N);
    return 0;
}
