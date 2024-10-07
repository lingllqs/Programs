#ifndef SMS_H
#define SMS_H
#include "../../2_数据结构/2_链表/1_双链表/list.h"

typedef struct stu_t
{
    unsigned int id;
    char name[20];
    unsigned int age;
    char gender[5];
    double score;
}Stu;

// 登陆界面
void showMenu();
void minsert(List *list);
void mremove(List *list);
void mmodify(List *list);
void mshowmesg(List *list);
void msearch(List *list);
void mquit(List *list);

void removeAction();
void searchAction();
void modifyAction();

void deleteById(List *list);
void deleteByName(List *list);
void deleteByAge(List *list);
void deleteByGender(List *list);

List* searchById(List *list);
List* searchByName(List *list);
List* searchByAge(List *list);
List* searchByGender(List *list);

int cmpById(void *dest, void *src);
int cmpByName(void *dest, void *src);
int cmpByAge(void *dest, void *src);
int cmpByGender(void *dest, void *src);

void print(void *data);
#endif 
