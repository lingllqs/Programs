#include "list.h"
#include <string.h>
#include <stdlib.h>


List* listInit(unsigned int type)
{
    List *list = (List *)malloc(sizeof(List));
    err_sys(NULL == list, "list malloc", goto ERR1);

    list->front = NULL;
    list->rear = NULL;
    list->size = 0;
    list->type = type;

    return list;

ERR1:
    return NULL;
}

Node* nodeInit(void *data, unsigned int type)// 结点初始化
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    err_sys(NULL == newnode, newnode malloc, goto ERR1);

    newnode->data = (void *)malloc(type);
    err_sys(newnode->data == NULL, data malloc, goto ERR2);

    memcpy(newnode->data, data, type);
    newnode->prev =  NULL;
    newnode->next = NULL;

    return newnode;
ERR1:
    return NULL;
ERR2:
    free(newnode);
    newnode = NULL;
    return NULL;
}

void push_back(List *list, void *data)
{
    if (!list || !data) return;

    Node *newnode = nodeInit(data, list->type);
    if (list->size == 0) {
        list->front = newnode;
        list->rear = newnode;
    }
    else {
        newnode->prev = list->rear;
        list->rear->next = newnode;
        list->rear = newnode;
    }
    list->size++;
}


void pop_back(List *list)
{
    if (!list || list->size == 0) return;
    Node *pnode = list->rear;
    if (list->size == 1) {
        list->front = list->rear = NULL;
    }
    else {
        list->rear = pnode->prev;
        list->rear->next = NULL;
    }
    freeNode(pnode);
    list->size--;
}

void pop_front(List *list)
{
    if (!list || list->size == 0) return;
    Node *pnode = list->front;
    if (list->size == 1) {
        list->front = list->rear = NULL;
    }
    else {
        list->front = pnode->next;
        list->front->prev = NULL;
    }
    freeNode(pnode);
    list->size--;

}
void pop_by_key(List *list, void *key, CMPFUNC cmp)
{
    if (list == NULL) return; 
    if ( list->size == 0) 
    {
        printf("数据为空\n");
        return;
    }
    Node *pnode = list->front;
    while (pnode)
    {
        if (cmp(key, pnode->data) == 0) {
            if (pnode == list->front) {
                pop_front(list);
            }
            else if (pnode == list->rear) {
                pop_back(list);
            }
            else {
                pnode->prev->next = pnode->next;
                pnode->next->prev = pnode->prev;
                list->size--;
                freeNode(pnode);
            }
        }
        pnode = pnode->next;
    }
}


int replace(List *list, void *key, void *newdata, CMPFUNC cmp)
{
    if (!list || list->size == 0) return -1;
    Node *pnode = list->front;
    int count = 0;
    while (pnode)
    {
        if (cmp(key, pnode->data) == 0) {
            memcpy(pnode->data, newdata, list->type);
            count++;
        }
        pnode = pnode->next;
    }
    return count;
}

Node* find_first_match(List *list, void *key, CMPFUNC cmp)
{
    if (!list || list->size == 0) return NULL;
    Node *pnode = list->front;
    while (pnode) 
    {
        if (cmp(key, pnode->data) == 0) return pnode;
        pnode = pnode->next;
    }
    return NULL;
}

List* find_all_match(List *list, void *key, CMPFUNC cmp)
{
    if (list == NULL) return NULL;
    List *rlist = listInit(list->type);
    Node *pnode = list->front;
    while (pnode)
    {
        if (cmp(key, pnode->data) == 0) {
            push_back(rlist, pnode->data);
        }
        pnode = pnode->next;
    }
    return rlist;
}

void for_each(List *list, PRIFUNC print)
{
    if (!list || list->size == 0) return;
    Node *pnode = list->front;
    while (pnode != NULL) 
    {
        print(pnode->data);
        pnode = pnode->next;
    }
}

void freeNode(Node *node)
{
    if (node != NULL) {
        free(node->data);
        node->data = NULL;
        node->prev = node->next = NULL;
        free(node);
        node = NULL;
    }
}

void freeList(List *list)
{
    if (NULL == list) return;
    Node *pnode = list->rear;
    while (pnode)
    {
        list->rear = pnode->prev;
        freeNode(pnode);
        pnode = list->rear;
    }
    list->front = list->rear = NULL;
    free(list);
    list = NULL;
}


