#include "list.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

List* listInit(int type)
{
    List *newlist = (List *)malloc(sizeof(List));
    if (!newlist) {
        printf("newlist malloc failure!\n");
        return NULL;
    }
    newlist->size = 0;
    newlist->type = type;
    newlist->front = NULL;
    newlist->rear = NULL;
    return newlist;
}

Node* nodeInit(Data *data, int type)
{
    Node *newnode = (Node *)malloc(sizeof(Node));
    if (!newnode) {
        printf("newnode malloc failure!\n");
        return NULL;
    }
    newnode->data = (Data *)malloc(type);
    if (!newnode->data) {
        printf("data malloc failure!\n");
        return NULL;
    }
    memcpy(newnode->data, data, type);
    newnode->next = NULL;
    return newnode;
}

int push_back_node(List *list, Data *data)
{
    Node *node = nodeInit(data, list->type);
    if (!list || !node) return -1;
    if (list->size == 0) {
        list->front = node;
        list->rear = node;
    }
    else {
        list->rear->next = node;
        list->rear = node;
    }
    list->size++;
    return 0;
}


int push_back_list(List *list, List *ilist)
{
    if (!list || !ilist || ilist->size == 0) return -1;
    if (list->size == 0) {
        List *plist = list;
        list = ilist;
        plist->front = plist->rear = NULL;
        plist->size = 0;
        /*free(plist);*/
        /*plist = NULL;*/
    }
    list->rear->next = ilist->front;
    list->rear = ilist->rear;
    list->size = list->size + ilist->size;
    ilist->front = ilist->rear = NULL;
    ilist->size = 0;
    /*free(ilist);*/
    /*ilist = NULL;*/
    return 0;
}

int push_front_node(List *list, Data *data)
{
    Node *node = nodeInit(data, list->type);
    if (!list || !node) return -1;
    if (list->size == 0) {
        list->front = node;
        list->rear = node;
    }
    else {
        node->next = list->front;
        list->front = node;
    }
    list->size++;
    return 0;
}

int push_front_list(List *list, List *ilist)
{
    if (!list || !ilist || ilist->size == 0) return -1;
    if (list->size == 0) {
        List *plist = list;
        list = ilist;
        plist->front = plist->rear = NULL;
        plist->size = 0;
        /*free(plist);*/
        /*plist = NULL;*/
        return 0;
    }
    ilist->rear->next = list->front;
    list->front = ilist->front;
    list->size = list->size + ilist->size;
    ilist->front = ilist->rear = NULL;
    ilist->size = 0;
    /*free(ilist);*/
    /*ilist = NULL;*/
    return 0;
}

int insert_pos_node(List *list, Data *data, int pos)
{
    Node *node = nodeInit(data, list->type);
    if (!list || !node || pos < 0 || pos > list->size - 1) return -1;
    if (pos == 0) {
        return push_front_node(list, data);
    }
    else if (pos == list->size - 1) {
        return push_back_node(list, data);
    }
    else {
        int i = 0;
        Node *pnode = list->front;
        for (i = 0; i < pos - 1; ++i)
        {
            pnode = pnode->next;
        }
        node->next = pnode->next;
        pnode->next = node;
        list->size++;
        return 0;
    }
}

int insert_pos_list(List *list, List *ilist, int pos)
{
    if (!list || !ilist || pos < 0 || pos > list->size-1 || ilist->size == 0) return -1;
    if (list->size == 0) {
        List *plist = list;
        list = ilist;
        plist->front = plist->rear = NULL;
        free(plist);
        plist = NULL;
        return 0;
    }
    if (pos == 0) {
        return push_front_list(list, ilist);
    }
    else if (pos == list->size - 1) {
        return push_back_list(list, ilist);
    }
    else {
        int i = 0;
        Node *pnode = list->front;
        for (i = 0; i < pos - 1; ++i)
        {
            pnode = pnode->next;
        }
        ilist->rear->next = pnode->next;
        pnode->next = ilist->front;
        list->size = list->size + ilist->size;
        ilist->front = ilist->rear = NULL;
        free(ilist);
        ilist = NULL;
        return 0;
    }
}


int pop_back_node(List *list)
{
    if (!list || list->size == 0) return -1;
    Node *pnode = list->front;
    if (list->size == 1) {
        free(pnode->data);
        pnode->data = NULL;
        free(pnode);
        pnode = NULL;
        list->front = list->rear = NULL;
        list->size--;
        return 0;
    }
    int i = 0;
    for (i = 0; i < list->size - 2; ++i)
    {
        pnode = pnode->next;
    }
    free(list->rear->data);
    list->rear->data = NULL;
    free(list->rear);
    list->rear = pnode;
    list->rear->next = NULL;
    list->size--;
    return 0;
}

int pop_front_node(List *list)
{
    if (!list || list->size == 0) return -1;
    Node *pnode = list->front;
    if (list->size == 1) {
        free(pnode->data);
        pnode->data = NULL;
        list->front = list->rear = NULL;
        list->size--;
        return 0;
    }
    list->front = list->front->next;
    pnode->next = NULL;
    free(pnode->data);
    pnode->data = NULL;
    free(pnode);
    pnode = NULL;
    list->size--;
    return 0;
}

int delete_pos_node(List *list, int pos)
{
    if (!list || list->size == 0 || pos < 0 || pos > list->size-1) return -1;
    Node *pnode = list->front;
    if (pos == 0) {
        return pop_front_node(list);
    }
    else if (pos == list->size - 1) {
        return pop_back_node(list);
    }
    else {
        int i = 0;
        for (i = 0; i < pos - 1; ++i)
        {
            pnode = pnode->next;
        }
        Node *cnode = pnode->next;
        pnode->next = cnode->next;
        free(cnode->data);
        cnode->data = NULL;
        free(cnode);
        cnode = NULL;
        list->size--;
        return 0;
    }
}


int modify(List *list, Data *key, Data *data, CMPFUNC cmpfunc)
{
    if (!list || !key) return -1;
    Node *pnode = list->front;
    int count = 0;
    while (pnode) {
        if (cmpfunc(key, pnode->data) == 0) {
            memcpy(pnode->data, data, list->type);
            count++;
        }
        pnode = pnode->next;
    }
    if (count == 0) {
        return -1;
    }
    return count;
}

Node* find_first_node(List *list, Data *data, CMPFUNC cmpfunc)
{
    if (!list || !data || list->size == 0) return NULL;
    Node *pnode = list->front;
    while (pnode) {
        if ((cmpfunc(data, pnode->data)) == 0) {
            return pnode;
        }
        pnode = pnode->next;
    }
    return NULL;
}


List* find_all_node(List *list, Data *data, CMPFUNC cmpfunc)
{
    if (!list || !data || list->size == 0) return NULL;
    List *flist = listInit(list->type);
    Node *pnode = list->front;
    int count = 0;
    while (pnode) {
        if (cmpfunc(data, pnode->data) == 0) {
            push_back_node(flist, pnode->data);
            count++;
        }
        pnode = pnode->next;
    }

    if (count == 0) {
        destroy_list(flist);
        return NULL;
    }
    return flist;
}

int save_list(const char *path, List *list, SAVEFUNC sfunc)
{
    if (!list || list->size == 0) return -1;
    FILE *fp = fopen(path, "w");
    if (!fp) return -1;
    fprintf(fp, "%d %d\n", list->size, list->type);
    Node *pnode = list->front;
    while (pnode) {
        sfunc(fp, pnode->data);
        pnode = pnode->next;
    }
    fclose(fp);
    return 0;
}

List* load_list(const char *path, LOADFUNC lfunc)
{
    FILE *fp = fopen(path, "r");
    int size, type;
    fscanf(fp, "%d %d", &size, &type);

    List *list = listInit(type);
    if (!list) return NULL;

    void *data = (void *)malloc(type);
    for (int i = 0; i < size; ++i) {
        lfunc(fp, data);//获取数据
        push_back_node(list, (Data *)data);
    }
    free(data);
    data = NULL;

    fclose(fp);
    return list;
}

void traverse(List *list, PRIFUNC pri)
{
    if (!list) return;
    Node *pnode = list->front;
    while (pnode) {
        pri(pnode->data);
        pnode = pnode->next;
    }
}

void destroy_list(List *list)
{
    if (!list) return;
    if (list) {
        if (list->size > 0) {
            Node *pnode = list->front;
            while (pnode) {
                pnode = pnode->next;
                free(list->front->data);
                list->front->data = NULL;
                free(list->front);
                list->front = pnode;
            }
        }
        list->front = list->rear = NULL;
        free(list);
        list = NULL;
    }
}







