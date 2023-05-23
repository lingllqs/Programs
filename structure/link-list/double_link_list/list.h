#ifndef LIST_H
#define LIST_H
#include <stdio.h>

#define err_sys(cond, mesg, proc) do {\
    if (cond) {\
        printf(#mesg" faliure!\n");\
        proc;\
    }\
}while(0);

typedef int (*CMPFUNC)(void *dest, void *src);
typedef void (*PRIFUNC)(void *data);

typedef struct node_t
{
    void *data;// 数据
    struct node_t *prev;// 指向前一个结点
    struct node_t *next;// 指向后一个结点
}Node;

typedef struct list_t
{
    struct node_t *front; // 指向第一个结点
    struct node_t *rear;  // 指向最后一个结点
    unsigned int size;    // 结点个数
    unsigned int type;    // 结点类型
}List;

List* listInit(unsigned int type);                              // 链表初始化
Node* nodeInit(void *data, unsigned int type);                  // 结点初始化
void push_back(List *list, void *data);                         // 尾插法
void pop_back(List *list);                                      // 头删法
void pop_front(List *list);                                     // 头删法
void pop_by_key(List *list, void *key, CMPFUNC cmp);            // 根据key值删除
int replace(List *list, void *key, void *newdata, CMPFUNC cmp); // 查找替换
Node* find_first_match(List *list, void *key, CMPFUNC cmp);     // 返回第一个找到的节点
List* find_all_match(List *list, void *key, CMPFUNC cmp);       // 返回所有找到的节点
void for_each(List *list, PRIFUNC print);                       // 遍历所有节点
void freeNode(Node *node);                                      // 销毁结点
void freeList(List *list);                                      // 销毁链表

#endif
