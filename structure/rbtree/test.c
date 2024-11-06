#include "rbtree.h"

struct data_t
{
    int a;
};

void pri(Data *data);
int cmp(Data *dest, Data *src);
int main(int argc, char *argv[])
{
    Data data1 = {10};
    Data data2 = {8};
    Data data3 = {9};
    Data data4 = {32};
    Data data5 = {9};
    RBTree *rbtree = createRBTree(sizeof(int));

    /*
     *RBNode *rbnode1 = createRBNode(&data1, sizeof(int));
     *RBNode *rbnode2 = createRBNode(&data2, sizeof(int));
     *RBNode *rbnode3 = createRBNode(&data3, sizeof(int));
     *RBNode *rbnode4 = createRBNode(&data4, sizeof(int));
     *RBNode *rbnode5 = createRBNode(&data5, sizeof(int));
     *RBNode *rbnode6 = createRBNode(&data5, sizeof(int));
     *RBNode *rbnode7 = createRBNode(&data5, sizeof(int));
     *printf("%u\n", key(rbnode5));
     */

    insert(rbtree, &data1, cmp);
    insert(rbtree, &data2, cmp);
    insert(rbtree, &data3, cmp);
    insert(rbtree, &data4, cmp);
    insert(rbtree, &data5, cmp);
    insert(rbtree, &data5, cmp);
    insert(rbtree, &data5, cmp);

    traverse(rbtree->root, pri);
    printf("------------------\n");

    /*printf("key before:%d\n", key(findNode(rbtree, &data5, cmp)));*/
    removeNode(rbtree, &data5, cmp);
    traverse(rbtree->root, pri);
    /*printf("key after:%d\n", key(findNode(rbtree, &data5, cmp)));*/
    printf("------------------\n");

    /*printf("before destroyTree\n");*/
    destroyTree(rbtree, false);
    /*printf("%u\n", size(*rbtree));*/
    /*printf("after destroyTree\n");*/
    /*destroyTree(rbtree, true);*/
    traverse(rbtree->root, pri);
    /*printf("traverse exit\n");*/
    return 0;
}
void pri(Data *data)
{
    printf("%d\n", data->a);
}

int cmp(Data *dest, Data *src)
{
    int d = (dest->a);
    int s = (src->a);
    return (d-s);
}
