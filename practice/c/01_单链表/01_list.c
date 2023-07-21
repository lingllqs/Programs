#include <stdio.h>
#include <stdlib.h>

typedef struct Node 
{
    int data;
    struct Node *next;
} Node;

typedef struct List
{
    Node *front;
    Node *end;
    int count;
} List;

Node *node_new(int data) 
{
    Node *new_node = (Node *)malloc(sizeof(Node));
    if (NULL == new_node) 
    {
        perror("malloc new node failure!\n");
        return NULL;
    }

    new_node->data = data;
    new_node->next = NULL;

    return new_node;
}

List *list_new()
{
    List *new_list = (List *)malloc(sizeof(List));
    if (NULL == new_list)
    {
        perror("malloc new list failure");
        return NULL;
    }

    new_list->front = new_list->end = NULL;
    new_list->count = 0;

    return new_list;
}

void push_back(List *list, Node *node)
{
    if (!list || !node) return;

    if (list->count == 0)
        {
            list->front = list->end = node;
        }
    else
    {
        list->end->next = node;
        list->end = node;
    }

    list->count++;
}

Node* pop_back(List *list)
{
    if (!list || list->count == 0) return NULL;

    Node *p = list->front;
    if (list->count == 1)
    {
        list->front = list->end = NULL;
        return p;
    }
    else
    {
        Node *n = p->next;
        while (n->next)
        {
            p = n;
            n = p->next;
        }
        list->end = p;
        list->end->next = NULL;
        return n;
    }
}

void for_each(List *list, void (*print)(void *))
{
    if (list && list->count > 0)
    {
        Node *p = list->front;
        while (p)
        {
            print(p);
            p = p->next;
            if (p)
            {
                printf("->");
            }
        }
    }
}

void list_destroy(List *list)
{
    if (list)
    {
        int size = list->count;
        Node *p = list->front;
        for (int i = 0; i < size; i++)
        {
            p = p->next;
            free(list->front);
            list->front = p;
        }
        free(list);
    }
}

void print(void *data)
{
    int tmp = *(int *)data;
    printf("%d", tmp);
}


int main(int argc, char *argv[]) 
{
    List *list = list_new();

    Node *node1 = node_new(5);
    Node *node2 = node_new(6);
    Node *node3 = node_new(9);

    push_back(list, node1);
    push_back(list, node2);
    push_back(list, node3);

    for_each(list, print);
    list_destroy(list);

    return 0;
}
