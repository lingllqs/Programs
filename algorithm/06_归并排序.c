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

int m[N];
void mergeSort(int *arr, int l, int r)
{
    /*int m[r+1];*/
    if (l == r) return;
    int mid = (l + r) >> 1;
    mergeSort(arr, l, mid);
    mergeSort(arr, mid + 1, r);
    int i = l, j = mid + 1, k = l;
    while (i <= mid && j <= r)
    {
        if (arr[i] >= arr[j]) {
            m[k++] = arr[j++];
        }
        else {
            m[k++] = arr[i++];
        }
    }
    while (i <=  mid) m[k++] = arr[i++];
    while (j <= r) m[k++] = arr[j++];
    for (i = l; i <= r; i++) arr[i] = m[i];
    pri(arr, N);
    printf("------------\n");
}

int main()
{
    srand(time(NULL));
    int arr[N];
    for (int i = 0; i < N; ++i)
        arr[i] = rand() % 20;
    pri(arr, N);
    mergeSort(arr, 0, N - 1);
    pri(arr, N);
    return 0;
}

