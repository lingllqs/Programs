#ifndef RBTREE_H
#define RBTREE_H


typedef enum
{
    SUCCESS,
    FAILURE,
} Status;

typedef enum
{
    RED,
    BLACK
} Color;

typedef struct RBTNode
{
    void *data;             // 数据域
    struct RBTNode *left;   // 左子结点
    struct RBTNode *right;  // 右子结点
    struct RBTNode *parent; // 双亲结点
    Color color;            // 结点颜色
} RBTNode;

typedef struct RBTree
{
    RBTNode *root; // 根结点
    int size;      // 结点个数
    int type;      // 数据类型大小
} RBTree;

RBTree *create_rbtree(int type);               // 创建红黑树
RBTNode *create_rbtnode(void *data, int size); // 创建红黑树结点
void left_rotate(RBTNode *node);

#endif // !RBTREE_H
