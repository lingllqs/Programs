#include <stdlib.h>
#include <string.h>

#include "rbtree.h"

RBTree *create_rbtree(int type)
{
    RBTree *new_rbtree = (RBTree *)malloc(sizeof(RBTree));
    if (!new_rbtree)
        return NULL;

    new_rbtree->root = NULL;
    new_rbtree->size = 0;
    new_rbtree->type = type;

    return new_rbtree;
}

RBTNode *create_rbtnode(void *data, int size)
{
    RBTNode *new_rbtnode = (RBTNode *)malloc(sizeof(RBTNode));
    if (!new_rbtnode)
        return NULL;

    new_rbtnode->data = (void *)malloc(size);
    if (!new_rbtnode->data)
    {
        free(new_rbtnode);
        return NULL;
    }
    memcpy(new_rbtnode->data, data, size);

    new_rbtnode->left = new_rbtnode->right = new_rbtnode->parent = NULL;
    new_rbtnode->color = RED;

    return new_rbtnode;
}
