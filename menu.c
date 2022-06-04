#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"
#include "student.h"
#include "menu.h"

int numCheck(char* str) {
    int n = strlen(str), cnt = 0;
    if (n != 10) return 0;
    for (int i = 0; i < n; i++) {
        if (str[i] >= '0' && str[i] <= '9') ++cnt;
    }
    return n == cnt;
}
// 该函数用于检验str是否是10位全数字字符串。（检查字符串）
/*
功能1：判断输入的是否全部是数字，如果不是数字，提示循环输入；
功能2：当输入的是数字时，则停止循环。
*/

void adminMenu() {

    printf("\t输入管理员密码以继续\n\t");
    char password[128], num[128];
    scanf("%s", &password);
    if (strcmp(password, "1234") != 0) {
        printf("\t软错误：密码输入错误，返回中...\n");
        return;
    }
    // 密码校验成功，进入管理员模式
    while (1) {
        int choice;

        printf("----------------------------------------------------------------");
        printf("\t       管理员模式\n");
        printf("\t 1.录入图书信息    \t2.修改图书信息\n");
        printf("\t 3.删除图书信息    \t4.查单个学生的借阅记录\n") ;
        printf("\t 5.查看所有图书信息\t 6.录入学生信息\n") ;
        printf("\t 0.返回首页\n");
        printf("\t请输入您的选择：\n\t");
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            return;
        case 1:
            addBook();
            break;
        case 2:
            editBook();
            break;
        case 3:
            delBook();
            break;
        case 4:
            printf("\t请输入学号\n\t");
            scanf("%s", num);
            if (!numCheck(num)) {
                printf("\t学号不合法，必须是10位数数字\n");
                break;
            }
            showStu(num);
            break;
        case 5:
            listBook();
            break;
        case 6:
            printf("\t请录入学号\n\t");
            scanf("%s", num);
            printf("%s", num);
            if (!numCheck(num)) {
                printf("\t学号不合法，必须是10位数数字\n");
                break;
            }
            addStu(num);
            break;
        default:
            printf("\t错误：暂无编号为%d的菜单，请重试\n", choice);
        }
    }
}
// 该函数打印一个管理员菜单（管理员模式菜单）
/*
功能1：显示各种菜单选项；
功能2：需要用户验证管理员密码，如果是预设的密码1234即通过，否则则返回-1；
功能3：验证密码完成之后才打印菜单，菜单中包含对书籍信息的增删查改选项。
*/


void stuMenu() {

    printf("\t输入学号以继续\n\t");
    char num[128];
    scanf("%s", &num);
    if (searchStu(num) == -1) {
        printf("\t软错误：未找到此学生，请联系管理员\n");
        return;
    }
    // 密码校验成功，进入管理员模式
    while (1) {

        int choice;
        printf("----------------------------------------------------------------");
        printf("\t       学生模式\n");
        printf("\t 1.借阅书籍 \t\t2.归还书籍\n");
        printf("\t 3.查询你的阅记录\n") ;
        printf("\t 0.返回首页\n");
        printf("\t请输入您的选择：\n\t");
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            return;
        case 1:
            borrowBook(num);
            break;
        case 2:
            returnBook(num);
            break;
        case 3:
            showStu(num);
            break;
        default:
            printf("\t错误：暂无编号为%d的菜单，请重试\n", choice);
        }
    }
}
// 该函数打印一个学生菜单，返回用户输入的选项。
/*
功能1：显示各种菜单选项
功能2：需要用户输入学号，调用numCheck()函数检验学号是否合法，如果不合法则返回-1;
功能3：学号合法之后才打印菜单，菜单中包含该学生对借还表的查询，增加（即借还）功能。(弄不来了）
*/

//菜单，用户友好为宗旨，提示信息必须要有，界面用户友好
void mainMenu() {

    int choice;
    printf("----------------------------------------------------------------");
    printf("\t\t程序设计与实践\t期末大作业\n");
    printf("\t\t欢迎光临图书管理系统\t\t\t本馆现有藏书%d本\n", countBook());
    printf("\t1.以学生身份继续\n");
    printf("\t2.以管理员身份继续\n");
    printf("\t0.退出系统\n");
    printf("\n\t请输入您的选择：\n");
    printf("\t");
    scanf("%d", &choice);
    switch (choice) {
    case 0:
        printf("\t感谢您的光临\n");
        system("PAUSE");
        exit(0);
    case 1:
        stuMenu();
        break;
    case 2:
        adminMenu();
        break;
    default:
        printf("\t错误：暂无编号为%d的菜单，请重试\n", choice);
    }
}
// 该函数打印一个主菜单
/*
主菜单是我们程序的主入口，是一个大菜单包含了管理员入口和学生入口。
功能1：显示各种菜单选项；
功能2：主菜单右上角可显示馆藏书籍的数量。
*/
