#include "sms.h"
#include <unistd.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../../2_数据结构/2_链表/1_双链表/list.h"



void minsert(List *list)
{
    Stu stu;
    printf("请输入学生的学号: ");
    scanf("%u%*c", &stu.id);
    printf("请输入学生的姓名: ");
    /*
     *fgets(stu.name, sizeof(stu.name), stdin);
     *if (stu.name[strlen(stu.name) - 1] == '\n') {
     *    stu.name[strlen(stu.name) - 1] = '\0';
     *}
     */
    scanf("%[^\n]%*c", stu.name);
    printf("请输入学生的年龄: ");
    /*getchar();*/
    scanf("%u%*c", &stu.age);
    printf("请输入学生的性别: ");
    /*getchar();*/
    scanf("%s%*c", stu.gender);
    printf("请输入学生的分数: ");
    /*getchar();*/
    scanf("%lf", &stu.score);
    push_back(list, &stu);
}

void mremove(List *list)
{
    if (list->size == 0) {
        printf("信息为空，删除失败\n");
        return;
    }
    while (true)
    {
        system("clear");
        removeAction();
        char ch;
        fflush(stdin);
        printf("请输入选项: ");
        scanf("%c", &ch);
        switch (ch) {
            case '1':
                deleteById(list);
                break;
            case '2':
                deleteByName(list);
                break;
            case '3':
                deleteByAge(list);
                break;
            case '4':
                deleteByGender(list);
                break;
            case '0':
                return;
            default:
                printf("unknown select\n");
                break;
        }
        printf("按回车继续!");
        getchar();
    }
}

void mmodify(List *list)
{
    if (!list || list->size == 0) return;
    while (true)
    {
        system("clear");
        modifyAction();
        char ch;
        printf("请输入选项: ");
        scanf("%c", &ch);
        switch (ch) {
            case '1':
                break;
            case '2':
                break;
            case '3':
                break;
            case '4':
                break;
            case '5':
                break;
            case '0':
                return;
            default:
                printf("unknown select\n");
                break;
        }
        printf("按回车继续!");
        getchar();
    }

}

void mshowmesg(List *list)
{
    for_each(list, print);
}

void msearch(List *list)
{
    if (list->size == 0) {
        printf("信息为空，查找失败\n");
        sleep(3);
        return;
    }
    List *rlist = NULL;
    while (true)
    {
        system("clear");
        searchAction();
        char ch;
        printf("请输入选项: ");
        scanf("%c", &ch);
        switch (ch) {
            case '1':
                rlist = searchById(list);
                break;
            case '2':
                rlist = searchByName(list);
                break;
            case '3':
                rlist = searchByAge(list);
                break;
            case '4':
                rlist = searchByGender(list);
                break;
            case '5':
                printf("+-------+---------------+-------+-------+-----------+\n");
                printf("| %-8s| %-16s| %-8s| %-8s| %-12s|\n", "学号", "姓名", "年龄", "性别", "分数");
                printf("+-------+---------------+-------+-------+-----------+\n");
                mshowmesg(rlist);
                printf("+-------+---------------+-------+-------+-----------+\n");
                getchar();
                break;
            case '0':
                mquit(rlist);
                return;
            default:
                printf("unknown select\n");
                break;
        }
        printf("按回车继续!");
        getchar();
    }
}

void mquit(List *list)
{
    freeList(list);
}

void print(void *data)
{
    Stu stu = *(Stu *)data;
    printf("| %-6u| %-10s\t| %-6u| %-s \t| %-10.2lf|\n", stu.id, stu.name, stu.age, stu.gender, stu.score);
}


void deleteById(List *list)
{
    printf("请输入要删除学生的学号: ");
    unsigned int id;
    scanf("%*c%u%*c", &id);
    printf("beforepop\n");
    pop_by_key(list, &id, cmpById);
    printf("afterpop\n");
}

void deleteByName(List *list)
{
    printf("请输入要删除学生的姓名: ");
    char name[20];
    scanf("%*c%s%*c", name);
    pop_by_key(list, name, cmpByName);
}

void deleteByAge(List *list)
{
    printf("请输入要删除学生的年龄: ");
    unsigned int age;
    scanf("%*c%u%*c", &age);
    pop_by_key(list, &age, cmpByAge);
}

void deleteByGender(List *list)
{
    printf("请输入要删除学生的性别: ");
    char gender[5];
    scanf("%*c%s%*c", gender);
    pop_by_key(list, gender, cmpByGender);
}

// 
List* searchById(List *list)
{
    printf("请输入要查找学生的学号: ");
    unsigned int id;
    scanf("%*c%u", &id);
    return find_all_match(list, &id, cmpById);
}

List* searchByName(List *list)
{
    printf("请输入要查找学生的姓名: ");
    char name[20];
    scanf("%*c%s", name);
    return find_all_match(list, name, cmpByName);
}

List* searchByAge(List *list)
{
    printf("请输入要查找学生的年龄: ");
    unsigned int age;
    scanf("%*c%u", &age);
    return find_all_match(list, &age, cmpByAge);
}
List* searchByGender(List *list)
{
    printf("请输入要查找学生的性别: ");
    char gender[5];
    scanf("%*c%s", gender);
    return find_all_match(list, gender, cmpByGender);
}

//
int cmpById(void *dest, void *src)
{
    unsigned int id = *(unsigned int *)dest;
    Stu stu = *(Stu *)src;
    return (id - stu.id);
}

int cmpByName(void *dest, void *src)
{
    const char *name = (const char *)dest;
    Stu stu  = *(Stu *)src;
    return strcmp(name, (const char *)stu.name);
}

int cmpByAge(void *dest, void *src)
{
    unsigned int age = *(unsigned int *)dest;
    Stu stu  = *(Stu *)src;
    return (age - stu.age);
}

int cmpByGender(void *dest, void *src)
{
    const char *gender = (const char *)dest;
    Stu stu  = *(Stu *)src;
    return strcmp(gender, (const char *)stu.gender);
}

void showMenu()
{
    printf("+--------------------+\n");
    printf("|   Welcome to SMS   |\n");
    printf("+--------------------+\n");
    printf("+--------------------+\n");
    printf("|   1. 插入学生信息  |\n");
    printf("+--------------------+\n");
    printf("|   2. 显示学生信息  |\n");
    printf("+--------------------+\n");
    printf("|   3. 删除学生信息  |\n");
    printf("+--------------------+\n");
    printf("|   4. 修改学生信息  |\n");
    printf("+--------------------+\n");
    printf("|   5. 查找学生信息  |\n");
    printf("+--------------------+\n");
    printf("|   0.   退出系统    |\n");
    printf("+--------------------+\n");
}

void removeAction()
{
    printf("+--------------------+\n");
    printf("|   请输入删除条件   |\n");
    printf("+--------------------+\n");
    printf("+--------------------+\n");
    printf("|   1. 根据学号删除  |\n");
    printf("+--------------------+\n");
    printf("|   2. 根据姓名删除  |\n");
    printf("+--------------------+\n");
    printf("|   3. 根据年龄删除  |\n");
    printf("+--------------------+\n");
    printf("|   4. 根据性别删除  |\n");
    printf("+--------------------+\n");
    printf("|   0.  返回主菜单   |\n");
    printf("+--------------------+\n");
}

void searchAction()
{
    printf("+--------------------+\n");
    printf("|   请输入查找条件   |\n");
    printf("+--------------------+\n");
    printf("+--------------------+\n");
    printf("|   1. 根据学号查找  |\n");
    printf("+--------------------+\n");
    printf("|   2. 根据姓名查找  |\n");
    printf("+--------------------+\n");
    printf("|   3. 根据年龄查找  |\n");
    printf("+--------------------+\n");
    printf("|   4. 根据性别查找  |\n");
    printf("+--------------------+\n");
    printf("|   5. 显示查找结果  |\n");
    printf("+--------------------+\n");
    printf("|   0.  返回主菜单   |\n");
    printf("+--------------------+\n");
}

void modifyAction()
{
    printf("+--------------------+\n");
    printf("|   请输入修改条件   |\n");
    printf("+--------------------+\n");
    printf("+--------------------+\n");
    printf("|   1. 根据学号修改  |\n");
    printf("+--------------------+\n");
    printf("|   2. 根据姓名修改  |\n");
    printf("+--------------------+\n");
    printf("|   3. 根据年龄修改  |\n");
    printf("+--------------------+\n");
    printf("|   4. 根据性别修改  |\n");
    printf("+--------------------+\n");
    printf("|   0.  返回主菜单   |\n");
    printf("+--------------------+\n");
}
