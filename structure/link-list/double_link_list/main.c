#include <stdio.h>
#include "list.h"

void print(void *data)
{
    int val = *(int *)data;
    printf("%d ", val);
}

int cmp(void *dest, void *src)
{
    int d = *(int *)dest;
    int s = *(int *)src;
    return (d -s);
}

int main()
{
    List *list = listInit(sizeof(int));
    int a = 2, b = 3;
    push_back(list, &a);
    push_back(list, &b);
    for_each(list, print);
    Node *node = find_first_match(list, &a, cmp);
    print(node->data);
    freeList(list);
}
