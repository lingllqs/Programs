#ifndef RBTREE_H
#define RBTREE_H

#include <stdbool.h>
#include <stdio.h>

#define err_sys(condition, message, handler) \
    do {                                     \
        if (condition) {                     \
            printf(#message " false!\n");    \
            handler;                         \
        }                                    \
    } while (0);

typedef enum {
    RED,
    BLACK
} Color;

typedef struct data_t Data;

typedef struct rbnode_t {
    struct data_t *data;      // 数据
    unsigned int key;         // 同种数据个数
    struct rbnode_t *parent;  // 父节点
    struct rbnode_t *left;    // 左子节点
    struct rbnode_t *right;   // 右子节点
    Color color;              // 节点颜色
} RBNode;

typedef struct rbtree_t {
    struct rbnode_t *root;
    unsigned int size;  // 节点个数
    unsigned int type;  // 数据类型大小
} RBTree;

typedef int(CMP)(Data *dest, Data *src);
typedef void(PRI)(Data *data);

RBTree *createRBTree(unsigned int type);              // 创建一个红黑树
RBNode *createRBNode(Data *data, unsigned int type);  // 初始化一个节点
bool leftRotate(RBTree *rbtree, RBNode *rbnode);
bool rightRotate(RBTree *rbtree, RBNode *rbnode);
RBNode *precursor(RBNode *rbnode);
RBNode *successor(RBNode *rbnode);
// 插入节点
// void insert(RBTree *rbtree, RBNode *rbnode, CMP *cmp);
void insert(RBTree *rbtree, Data *data, CMP *cmp);
// 删除结点
// RBNode* removeNode(RBTree *rbtree, RBNode *rbnode);
RBNode *removeNode(RBTree *rbtree, Data *data, CMP *cmp);
// 调整
void setColor(RBNode *rbnode, Color color);
void fixAfterInsert(RBTree *rbtree, RBNode *rbnode);
void fixAfterRemove(RBTree *rbtree, RBNode *rbnode);
// 获取信息
unsigned int key(RBNode *rbnode);
Color colorOf(RBNode *rbnode);
RBNode *leftOf(RBNode *rbnode);
RBNode *rightOf(RBNode *rbnode);
RBNode *parentOf(RBNode *rbnode);
unsigned int size(RBTree rbtree);

void traverse(RBNode *root, PRI *pri);                   // 红黑树遍历
RBNode *findNode(RBTree *rbtree, Data *data, CMP *cmp);  // 查找结点
void destroyNode(RBNode *rbnode);                        // 红黑树结点删除
// 红黑树删除
// flag标志为true表示释放rbtree的所有结点数据，但本身树的管理结点没有释放
void destroyTree(RBTree *rbtree, bool flag);
void freeTree(RBNode *root);
// 数据保存

#endif /* ifndef RBTREE_H */
