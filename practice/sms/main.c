#include "sms.h"
#include <unistd.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int main()
{
    List *list = listInit(sizeof(Stu));
    while (true)
    {
        system("clear");
        showMenu();
        char ch;
        printf("请选择功能选项: ");
        scanf("%c%*c", &ch);
        switch (ch) {
            case '1':
                minsert(list);
                break;
            case '2':
                printf("+-------+---------------+-------+-------+-----------+\n");
                printf("| %-8s| %-16s| %-8s| %-8s| %-12s|\n", "学号", "姓名", "年龄", "性别", "分数");
                printf("+-------+---------------+-------+-------+-----------+\n");
                mshowmesg(list);
                printf("+-------+---------------+-------+-------+-----------+\n");
                break;
            case '3':
                mremove(list);
                break;
            case '4':
                mmodify(list);
                break;
            case '5':
                msearch(list);
                break;
            case '0':
                mquit(list);
                return 0;
            default:
                printf("unknown faq!");
                break;
        }
        getchar();
        printf("按回车继续!");
        getchar();
    }
    return 0;
}
