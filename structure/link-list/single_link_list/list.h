#ifndef LIST_H
#define LIST_H
#include <stdio.h>

typedef struct data_t Data;

typedef struct node_t//结点数据结构
{
    Data *data;//数据
    struct node_t *next;//指向下一个结点的指针
}Node;

typedef struct list_t//链表数据结构
{
    struct node_t *front;//指向链表的第一个结点
    struct node_t *rear;//指向链表的最后一个结点
    int size;//结点个数
    int type;//结点数据的大小
}List;

typedef int (*CMPFUNC)(Data *dest, Data *src);//比较函数接口，用户根据自己的数据类型实现
typedef void (*PRIFUNC)(Data *data);//打印函数接口，用户根据自己的数据类型实现单个数据打印
typedef void (*SAVEFUNC)(FILE *fp, Data *data);//
typedef void (*LOADFUNC)(FILE *fp, void *data);

// 初始化
List* listInit(int type);//链表初始化
Node* nodeInit(Data *data, int type);//结点初始化，用户一般不需要调
                                     //
// 插入方法
int push_back_node(List *list, Data *data);//尾插法插入节点
int push_back_list(List *list, List *ilist);//尾插法插入链表
int push_front_node(List *list, Data *data);
int push_front_list(List *list, List *ilist);
int insert_pos_node(List *list, Data *data, int pos);//指定位置插入节点0为第一个位置
int insert_pos_list(List *list, List *ilist, int pos);//指定位置插入链表

// 删除方法
int pop_back_node(List *list);//尾删法删除节点
int pop_front_node(List *list);
int delete_pos_node(List *list, int pos);//指定位置删除节点

// 修改方法
int modify(List *list, Data *key, Data *data, CMPFUNC cmpfunc);//修改所有匹配的数据

// 查询方法
Node* find_first_node(List *list, Data *data, CMPFUNC cmpfunc);//从头查找第一个匹配的数据
List* find_all_node(List *list, Data *data, CMPFUNC cmpfunc);

// 数据持久化方法
int save_list(const char *path, List *list, SAVEFUNC sfunc);//保存数据到文件
List* load_list(const char *path, LOADFUNC lfunc);//读取文件数据

// 遍历方法
void traverse(List *list, PRIFUNC pri);//遍历链表
                                       //
// 释放资源
void destroy_list(List *list);//销毁链表

#endif /* ifndef SIN */
