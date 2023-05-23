#include "01_list.h"
#include <stdlib.h>
#include <stdio.h>

typedef struct stu_t
{
    int id;
    char name[64];
    int age;
    char gender;
}Stu;

int cmpfunc(Data *dest, Data *src)
{
    Stu sdest = *(Stu *)dest;
    Stu ssrc = *(Stu *)src;
    return ((sdest.id) - (ssrc.id));
}

void pri(Data *pdata)
{
    Stu *data = (Stu *)pdata;
    printf("\033[31;40m%d %s %d %c\033[0m\n", data->id, data->name, data->age, data->gender);
}

void sfunc(FILE *fp, Data *sdata)
{
    Stu *data = (Stu*)sdata;
    fprintf(fp, "%d %s %d %c\n", data->id, data->name, data->age, data->gender);
}

void lfunc(FILE *fp, void *ldata)
{
    Stu *data = (Stu*)ldata;
    /*data = (Data *)malloc(sizeof(Data));*/
    fscanf(fp, "%d %s %d %c", &(data->id), data->name, &(data->age), &(data->gender));
}

int main(int argc, char *argv[])
{
    List *list = listInit(sizeof(Stu));

    Stu data1 = {1, "张三", 20, 'M'};
    Stu data2 = {2, "李四", 18, 'F'};
    Stu data3 = {3, "王五", 22, 'M'};
    Stu data4 = {4, "老六", 99, 'F'};

    push_back_node(list, (Data *)&data1);
    push_back_node(list, (Data *)&data2);
    push_back_node(list, (Data *)&data3);
    push_back_node(list, (Data *)&data4);
    push_back_node(list, (Data *)&data4);


    traverse(list, pri);
    putchar(10);

    int ret = modify(list, (Data*)&data4, (Data *)&data1, cmpfunc);
    if (ret > 0) {
        traverse(list, pri);
    }

    /*
     *push_back_list(list, list1);
     *traverse(list, pri);
     *putchar(10);
     */

/*
 *    Node *node = find_first_node(list, (Data*)&data4, cmpfunc);
 *    pri((Data*)node->data);
 *
 *    List *flist = find_all_node(list, (Data*)&data4, cmpfunc);
 *    if (flist) {
 *        traverse(flist, pri);
 *        destroy_list(flist);
 *    }
 *
 */

    save_list("./b.txt", list, sfunc);

    /*delete_pos_node(list, 4);*/
    /*traverse(list, pri);*/

    destroy_list(list);

    /*
     *FILE *fp = fopen("b.txt", "r");
     *Stu data;
     *int size, type;
     *fscanf(fp, "%d %d\n", &size, &type);
     *fscanf(fp, "%d %s %d %c", &data.id, data.name, &data.age, &data.gender);
     *printf("%d %s %d %c\n", data.id, data.name, data.age, data.gender);
     *fscanf(fp, "%d %s %d %c", &data.id, data.name, &data.age, &data.gender);
     *printf("%d %s %d %c\n", data.id, data.name, data.age, data.gender);
     */

    /*
     *List *newlist = load_list("b.txt", lfunc);
     *printf("--------\n");
     *traverse(newlist, pri);
     *destroy_list(newlist);
     */

    return 0;
}
