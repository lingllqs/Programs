#include "rbtree.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
 *1.节点是红色或黑色。
 *2.根是黑色。
 *3.所有叶子都是黑色（叶子是NIL节点）。
 *4.每个红色节点必须有两个黑色的子节点。（从每个叶子到根的所有路径上不能有两个连续的红色节点。）
    根据2-3-4树演变，2-3-4树是一棵满多叉树，2表示该节点有两个分叉，以此类推
    把2-3-4树的每一个节点看作，必须有且只有一个黑色节点，对3节点和4节点来说
    其余1个/2个分叉展开成红黑树节点就是红色节点
 *5.从任一节点到其每个叶子的所有简单路径都包含相同数目的黑色节点（简称黑高）。
    由一棵2-3-4树展开成红黑树必然满足该条件
 */

RBTree* createRBTree(unsigned int type)
{
    RBTree *rbtree = (RBTree *)malloc(sizeof(RBTree));
    err_sys(rbtree == NULL, rbtree malloc, goto ERR1);
    rbtree->root = NULL;
    rbtree->size = 0;
    rbtree->type = type;
    return rbtree;

ERR1:
    return NULL;
}

RBNode* createRBNode(Data *data, unsigned int type)
{
    RBNode *rbnode = (RBNode *)malloc(sizeof(RBNode));
    err_sys(NULL == rbnode, rbnode malloc, goto ERR1);

    rbnode->data = (Data *)malloc(type);
    err_sys(NULL == rbnode->data, data malloc, goto ERR2);
    memcpy(rbnode->data, data, type);

    rbnode->left = rbnode->right = rbnode->parent = NULL;
    rbnode->key = 1;
    rbnode->color = RED;
    /*printf("createRBNodeexit\n");*/
    return rbnode;

ERR1:
    return NULL;
ERR2:
    free(rbnode);
    rbnode = NULL;
    return NULL;
}


bool leftRotate(RBTree *rbtree, RBNode *rbnode)
{
    if (!rbnode) return false;
    RBNode *pp = rbnode->parent;
    RBNode *pr = rbnode->right;
    rbnode->right = pr->left;
    if (pr->left)
    {
        pr->left->parent = rbnode;
    }
    pr->parent = pp;
    if (pp)
    {
        if (rbnode == pp->left)
        {
            pp->left = pr;
        }
        else
        {
            pp->right = pr;
        }
    }
    else
    {
        rbtree->root = pr;
    }
    pr->left = rbnode;
    rbnode->parent = pr;
    return true;
}

bool rightRotate(RBTree *rbtree, RBNode *rbnode)
{
    if (!rbnode) return false;
    RBNode *pp = rbnode->parent;
    RBNode *pl = rbnode->left;
    rbnode->left = pl->right;
    if (pl->right)
    {
        pl->right->parent = rbnode;
    }
    pl->parent = pp;
    if (pp)
    {
        if (rbnode == pp->left)
        {
            pp->left = pl;
        }
        else
        {
            pp->right = pl;
        }
    }
    else
    {
        rbtree->root = pl;
    }
    pl->right = rbnode;
    rbnode->parent = pl;
    return true;
}

// 寻找前驱结点,小于当前结点的最大值
RBNode* precursor(RBNode *rbnode)
{
    if (!rbnode) return NULL;
    if (rbnode->left)
    {
        RBNode *p = rbnode->left;
        while (p->right)
        {
            p = p->right;
        }
        return p;
    }
    // 当前结点没有左孩子
    else
    {
        if (!rbnode->parent)
        {
            return NULL;
        }
        // 当前结点不是根节点
        else
        {
            RBNode *pc = rbnode;
            RBNode *pp = rbnode->parent;
            while (pp || pp == pp->left)
            {
                pc = pp;
                pp = pp->parent;
            }
            return pp;
        }
    }
}
// 寻找后继结点，大于当前结点的最小值
RBNode* successor(RBNode *rbnode)
{
    if (!rbnode) return NULL;
    if (rbnode->right)
    {
        RBNode *p = rbnode->right;
        while (p->left)
        {
            p = p->left;
        }
        return p;
    }
    // 当前结点没有右孩子
    else
    {
        if (!rbnode->parent)
        {
            return NULL;
        }
        else
        {
            RBNode *pc = rbnode;
            RBNode *pp = rbnode->parent;
            while (pp || pp == pp->right)
            {
                pc = pp;
                pp = pp->parent;
            }
            return pp;
        }
    }
}

void insert(RBTree *rbtree, Data *data, CMP *cmp)
{
    RBNode *rbnode = createRBNode(data, rbtree->type);
    if (!rbtree || !rbnode) return;

    // 根节点为空
    if (!rbtree->root)
    {
        rbtree->root = rbnode;
    }
    else
    {
        RBNode *proot = rbtree->root;
        RBNode *pcur = NULL;
        while (proot)
        {
            /*printf("enter do while\n");*/
            pcur = proot;
            if (cmp(rbnode->data, proot->data) > 0)
            {
                proot = proot->right;
                /*printf("enter right\n");*/
            }
            else if (cmp(rbnode->data, proot->data) < 0)
            {
                proot = proot->left;
                /*printf("enter left\n");*/
            }
            else
            {
                proot->key++;
                destroyNode(rbnode);
                return;
            }
            /*
             *if (!proot)
             *{
             *    printf("null\n");
             *}
             */
        }
        // 找到插入点
        if (cmp(rbnode->data, pcur->data) > 0)
        {
            /*printf("succ\n");*/
            pcur->right = rbnode;
        }
        else
        {
            pcur->left = rbnode;
        }
        rbnode->parent = pcur;
    }
    rbtree->size++;
    /*printf("fixAfterInsert前\n");*/
    fixAfterInsert(rbtree, rbnode);
    /*printf("fixAfterInsert后\n");*/
    /*printf("插入了一个节点\n");*/
}


void setColor(RBNode *rbnode, Color color)
{
    if (rbnode)
    {
        rbnode->color = color;
    }
}

void fixAfterInsert(RBTree *rbtree, RBNode *rbnode)
{
    /*setColor(rbnode, RED);*/
    // rbnode的父结点是红色需要调整
    // 总共有8种情况
    while ( rbnode != rbtree->root && rbnode->parent->color == RED && rbnode)
    {
        /*printf("fixAfterInsert中\n");*/
        // 当前结点的父结点是爷爷结点的左孩子
        if (rbnode->parent == rbnode->parent->parent->left)
        {
            /*
             *color colorof(rbnode *rbnode)
             *{
             *    // 空结点默认为黑色
             *    return rbnode == null ? black : rbnode->color;
             *}
             */
            // 此处注意不能用rbnode->parent->parent->right->color == RED 判断
            // 因为当叔叔节点为空时会出错
            if (colorOf(rightOf(parentOf(parentOf(rbnode)))) == RED)
            {
                setColor(rbnode->parent, BLACK);
                setColor(rbnode->parent->parent->right, BLACK);
                setColor(rbnode->parent->parent, RED);
                rbnode = rbnode->parent->parent;
            }
            else
            {
                if (rbnode == rbnode->parent->right)
                {
                    rbnode = rbnode->parent;
                    leftRotate(rbtree, rbnode);
                }
                setColor(rbnode->parent, BLACK);
                setColor(rbnode->parent->parent, RED);
                rightRotate(rbtree, rbnode->parent->parent);
            }
        }
        // 当前结点的父结点是爷爷结点的右孩子
        else
        {
            if (colorOf(leftOf(parentOf(parentOf(rbnode)))) == RED)
            {
                setColor(rbnode->parent, BLACK);
                setColor(rbnode->parent->parent->left, BLACK);
                setColor(rbnode->parent->parent, RED);
                rbnode = rbnode->parent->parent;
            }
            else
            {
                if (rbnode == rbnode->parent->left)
                {
                    rbnode = rbnode->parent;
                    rightRotate(rbtree, rbnode);
                }
                setColor(rbnode->parent, BLACK);
                setColor(rbnode->parent->parent, RED);
                leftRotate(rbtree, rbnode->parent->parent);
            }
        }
    }
    // 若进入循环，当前结点为根节点，调整颜色
    setColor(rbtree->root, BLACK);
}


/*RBNode* removeNode(RBTree *rbtree, RBNode *rbnode)*/
/*{*/
    /*if (rbnode->key > 1)*/
    /*{*/
        /*rbnode->key--;*/
        /*return NULL;*/
    /*}*/
    /*[>RBNode *retNode = createRBNode(rbnode->data, rbtree->type);<]*/
    /*// 有左右孩子节点，可以找前驱或后继替代删除*/
    /*if (rbnode->left && rbnode->right)*/
    /*{*/
        /*// 找到前驱或者后继结点来替换要删除的结点*/
        /*RBNode *reDelNode = precursor(rbnode);*/
        /*[>RBNode *reDelNode = successor(rbnode);<]*/
        /*// 把替代节点的数据拷贝到要删除的节点*/
        /*memcpy(rbnode->data, reDelNode->data, rbtree->type);*/
        /*rbnode = reDelNode;*/
    /*}*/

    /*// 若第一个判断条件成立，则当前结点(rbnode)已指向了前驱或后继结点*/
    /*// 不管何种情况，此时的rbnode要么是叶子节点，要么是叶子节点的父节点(且是其父节点的唯一子节点)*/
    /*// 获取当前结点的子节点情况*/
    /*RBNode *repNode = rbnode->left ? rbnode->left : rbnode->right;*/

    /*// 分情况*/
    /*// 当前结点rbnode有子节点, 也就是前驱或后继节点不是叶子节点,或者rbnode是根节点*/
    /*// childNode 一定为红色*/
    /*if (repNode)*/
    /*{*/
        /*repNode->parent = rbnode->parent;*/
        /*if (!rbnode->parent)*/
        /*{*/
            /*rbtree->root = repNode;*/
        /*}*/
        /*else if (rbnode == rbnode->parent->left)*/
        /*{*/
            /*rbnode->parent->left = repNode;*/
        /*}*/
        /*else*/
        /*{*/
            /*rbnode->parent->right = repNode;*/
        /*}*/

        /*destroyNode(rbnode);*/

        /*[>printf("11111111111\n");<]*/
        /*[>if (rbnode->color == BLACK)<]*/
        /*fixAfterRemove(rbtree, repNode);*/
    /*}*/
    /*
     *else if (!rbnode->parent)
     *{
     *    rbtree->root = NULL;
     *}
     */
    /*// 当前结点没有子节点*/
    /*else*/
    /*{*/
        /*// rbnode是根节点*/
        /*if (rbnode == rbtree->root)*/
        /*{*/
            /*destroyNode(rbnode);*/
            /*rbtree->root = NULL;*/
        /*}*/
        /*// 删除的是叶子节点*/
        /*// 需要先调整后删除*/
        /*else*/
        /*{*/
            /*[>printf("2222222222222222\n");<]*/
            /*fixAfterRemove(rbtree, rbnode);*/
            /*[>printf("before destroyNode\n");<]*/
            /*destroyNode(rbnode);*/

        /*}*/
    /*}*/

    /*// 返回删除节点的数据*/
    /*rbtree->size--;*/
    /*[>return retNode;<]*/
    /*return NULL;*/
/*}*/

RBNode* findNode(RBTree *rbtree, Data *data, CMP *cmp)
{
    if (!rbtree || !rbtree->root || !data) return NULL;
    RBNode *proot = rbtree->root;
    while (proot)
    {
        if (cmp(data, proot->data) == 0)
        {
            return proot;
        }
        else
        {
            if (cmp(data, proot->data) > 0)
            {
                proot = proot->right;
            }
            else if (cmp(data, proot->data) < 0)
            {
                proot = proot->left;
            }
        }
    }
    printf("find NULL\n");
    return NULL;
}

RBNode* removeNode(RBTree *rbtree, Data *data, CMP *cmp)
{
    RBNode *rbnode = findNode(rbtree, data, cmp);
    if (!rbnode) return NULL;

    if (rbnode->key > 1)
    {
        rbnode->key--;
        return rbnode;
    }
    // rbnode的key等于1
    RBNode *retNode = createRBNode(rbnode->data, rbtree->type);
    // 有左右孩子节点，可以找前驱或后继替代删除
    if (rbnode->left && rbnode->right)
    {
        // 找到前驱或者后继结点来替换要删除的结点
        RBNode *reDelNode = precursor(rbnode);
        /*RBNode *reDelNode = successor(rbnode);*/
        // 把替代节点的数据拷贝到要删除的节点
        memcpy(rbnode->data, reDelNode->data, rbtree->type);
        rbnode = reDelNode;
    }

    // 若第一个判断条件成立，则当前结点(rbnode)已指向了前驱或后继结点
    // 不管何种情况，此时的rbnode要么是叶子节点，要么是叶子节点的父节点(且是其父节点的唯一子节点)
    // 获取当前结点的子节点情况
    RBNode *repNode = rbnode->left ? rbnode->left : rbnode->right;

    // 分情况
    // 当前结点rbnode有子节点, 也就是前驱或后继节点不是叶子节点,或者rbnode是根节点
    // childNode 一定为红色
    if (repNode)
    {
        repNode->parent = rbnode->parent;
        if (!rbnode->parent)
        {
            rbtree->root = repNode;
        }
        else if (rbnode == rbnode->parent->left)
        {
            rbnode->parent->left = repNode;
        }
        else
        {
            rbnode->parent->right = repNode;
        }

        destroyNode(rbnode);

        if (rbnode->color == BLACK)
        fixAfterRemove(rbtree, repNode);
    }
    else if (!rbnode->parent)
    {
        rbtree->root = NULL;
    }
    // 当前结点没有子节点
    else
    {
        // rbnode是根节点
        if (rbnode == rbtree->root)
        {
            destroyNode(rbnode);
            rbtree->root = NULL;
        }
        // 删除的是叶子节点
        // 需要先调整后删除
        else
        {
            fixAfterRemove(rbtree, rbnode);
            destroyNode(rbnode);

        }
    }

    // 返回删除节点的数据
    rbtree->size--;
    return NULL;
}

void fixAfterRemove(RBTree *rbtree, RBNode *rbnode)
{
    /*printf("enter fixAfterRemove\n");*/
    // 删除的是叶子节点为黑色
    while (rbnode != rbtree->root && colorOf(rbnode) == BLACK)
    {
        // rbnode节点是父节点的左孩子
        if (rbnode == leftOf(parentOf(rbnode)))
        {
            // 找对兄弟节点
            RBNode *bronode = rightOf(parentOf(rbnode));
            // bronode是红色，而rbnode是黑色，那么bronode的子节点一定是黑色
            // 而且有两个黑色子节点(因为根据2-3-4树
            // 把每一个节点看作，必须有且只有一个黑色节点，对3节点和4节点来说
            // 展开的分叉必定是红色节点)
            // 接下来的左旋会使bronode的左孩子(黑色)挂在rbnode节点的父节点的右子树
            if (colorOf(bronode) == RED)
            {
                setColor(bronode, BLACK);
                setColor(parentOf(rbnode), RED);
                leftRotate(rbtree, parentOf(rbnode));
                bronode = rightOf(parentOf(rbnode));
            }
            // 此时rbnode的兄弟节点一定为黑色
            // 情况1
            if (colorOf(leftOf(bronode)) == BLACK && colorOf(rightOf(bronode)) == BLACK)
            {
                setColor(bronode, RED);
                rbnode = parentOf(rbnode);
                // 此时以rbnode节点的父节点为根节点的左子树比右子树
                // 在全路径上少了一个黑色节点
                // 利用递归思想往上不断循环判断
                // 停止循环时机如下：
                // 1。当前rbnode节点为红色，只需设其为黑色即可
                // 2。当前rbnode节点的bronode为红色，执行完while循环内相应判断语句后
                //    rbnode节点的bronode节点变为黑色，继续执行while循环内相应判断语句
                //    (1)当符合当前if语句条件继续
                //    (2)当符合以下的else语句条件，执行完后红黑树保持平衡
            }
            // 兄弟节点的子节点至少有一个为红色
            // 情况2
            else
            {
                // 满足这种情况的时候
                // 当前else内语句执行完后，红黑树必定平衡
                if (colorOf(rightOf(bronode)) == BLACK)
                {
                    // bronode的左节点为红色
                    // 左旋和右旋不改变红黑树的有序性
                    // 对应2-3-4数情况 #代表黑色，@代表红色
//                       /                    /
//                      #(@)                 #(@)
//                     / \                  / \
//            (rbnode)#   #(bronode)       #   #
//                   / \ / \    -->       / \ / \
//                  #  # @  #            #  # #  @
//                      / \                     / \
//                     #   #                   #   #
                    setColor(leftOf(bronode), BLACK);
                    setColor(bronode, RED);
                    rightRotate(rbtree, bronode);
                    bronode = rightOf(parentOf(rbnode));
                }
//              D为待删除结点，S为bronode子节点都为黑色时使其为红色rbnode
//              往上传递调整，也就是上面的情况1可能会进入此调整
//                      /                            /
//             (parent)#(@)                (bronode)#(@)
//                    / \                          / \
//                   #   #(bronode)   --> (parent)#   #
//                  / \ / \                      / \ / \
//              (D)#  # #  @                    #  # #  #
//                        / \                  / \
//                       #   #             (D)#   #(S)
                setColor(bronode, colorOf(parentOf(rbnode)));
                setColor(parentOf(rbnode), BLACK);
                setColor(rightOf(bronode), BLACK);
                leftRotate(rbtree, parentOf(rbnode));
                rbnode = rbtree->root;
            }
        }
        // rbnode节点是父节点的右孩子
        // rbnode == rightOf(parentOf(rbnode))
        else
        {
            // 找到rbnode节点的兄弟节点
            RBNode *bronode = leftOf(parentOf(rbnode));
            if (colorOf(bronode) == RED)
            {
                setColor(bronode, BLACK);
                setColor(parentOf(rbnode), RED);
                rightRotate(rbtree, parentOf(rbnode));
                bronode = leftOf(parentOf(rbnode));
            }
            if (colorOf(leftOf(bronode)) == BLACK && colorOf(rightOf(bronode)) == BLACK)
            {
                setColor(bronode, RED);
                rbnode = parentOf(rbnode);
            }
            // 兄弟节点有红色子节点
            else
            {
                if (colorOf(leftOf(bronode)) == BLACK)
                {
                    setColor(bronode, RED);
                    setColor(rightOf(bronode), BLACK);
                    leftRotate(rbtree, bronode);
                    bronode = leftOf(parentOf(rbnode));
                }
                setColor(bronode, colorOf(parentOf(rbnode)));
                setColor(parentOf(rbnode), BLACK);
                setColor(leftOf(bronode), BLACK);
                rightRotate(rbtree, parentOf(rbnode));
                rbnode = rbtree->root;
            }
        }
    }

    setColor(rbnode, BLACK);
}

void traverse(RBNode *root, PRI *pri)
{
    if (root)
    {
        traverse(root->left, pri);
        for (int i = 0; i < root->key; ++i)
            pri(root->data);
        traverse(root->right, pri);
    }
    /*printf("traverse\n");*/
}

void destroyNode(RBNode *rbnode)
{
    if (rbnode)
    {
        if (rbnode->parent)
        {
            // 删除前需要使rbnode的父节点与其脱钩
            if (rbnode == rbnode->parent->left)
            {
                rbnode->parent->left = NULL;
            }
            else if (rbnode == rbnode->parent->right)
            {
                rbnode->parent->right = NULL;
            }
            /*rbnode->parent = NULL;*/
        }
        rbnode->left = rbnode->right = rbnode->parent = NULL;
        free(rbnode->data);
        rbnode->data = NULL;
        free(rbnode);
        rbnode = NULL;
    /*printf("enter destroyNode\n");*/
    }
}

/*
 *typedef struct rbtree_t
 *{
 *    struct rbnode_t *root;
 *    unsigned int size;  // 节点个数
 *    unsigned int type;   // 数据类型大小
 *}RBTree;
 */
void destroyTree(RBTree *rbtree, bool flag)
{
    freeTree(rbtree->root);
    /*rbtree->root = NULL;*/
    if (rbtree)
    {
        /*printf("enter free\n");*/
        rbtree->root = NULL;
        if (flag)
        {
            free(rbtree);
            rbtree = NULL;
        }
        else
        {
            rbtree->size = 0;
        }
    }
}

void freeTree(RBNode *root)
{
    if (root)
    {
        freeTree(root->left);
        freeTree(root->right);
        destroyNode(root);
    }

}

unsigned int key(RBNode *rbnode)
{
    return rbnode->key;
}

Color colorOf(RBNode *rbnode)
{
    // 空结点默认为黑色
    return rbnode == NULL ? BLACK : rbnode->color;
}

RBNode* leftOf(RBNode *rbnode)
{
    return rbnode ? rbnode->left : NULL;
}

RBNode* rightOf(RBNode *rbnode)
{
    return rbnode ? rbnode->right : NULL;
}

RBNode* parentOf(RBNode *rbnode)
{
    return rbnode ? rbnode->parent : NULL;
}

unsigned int size(RBTree rbtree)
{
    return rbtree.size;
}
