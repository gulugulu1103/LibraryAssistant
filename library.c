#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include "class.h"
#include "library.h"

int countBook()
{
    int record = 0;
    Book book;
    errno = 0;
    FILE* fp = fopen(".\\library.dat", "r+");
    if (!fp) {
        return 0;
    }
    while (!feof(fp))
    {
        fread(&book, sizeof(Book), 1, fp);
        record++;
    }
    fclose(fp);
    return record - 1;
}

void listBook()
{
    int i, number = 0, n;
    n = countBook();
    Book book;
    if (n <= 0)
    {
        printf("\t暂无书目，先加书目！\n\t"); 
        system("PAUSE");
        return;
    }
    else
    {
        errno = 0;
        FILE* fp = fopen(".\\library.dat", "r+");
        if (!fp) {
            printf("\t错误：无法打开library.dat，错误代码%d：%s\n\t", errno, strerror(errno));
            system("PAUSE");
            exit(0);
        }
        printf("|**********************************************************************|\n");
        printf("\n\n");
        printf("\t%-16s%-10s%-6s\n", "书名", "    类型","数量");
        for (int i = 0; i < n; i++)
        {
            fread(&book, sizeof(Book), 1, fp);
            printf("\t%d | 《%-16s》 | %-10s | %-6d\n", number, book.name, book.type, book.num);
            number++;
        }
        printf("\n\n");
        printf("|**********************************************************************|\n");
        printf("\n\n");
        fclose(fp);
    }
    printf("\t");
    system("pause");
    return;
}
void addBook()
{
    int a = access(".\\.library.dat", F_OK);//access函数用来判断文件是否存在 
    if (a == 0)//文件存在,直接进行add操作 
    {
        Book ibook;//用以添加额外书籍的变量ibook 
        Book book;// 初始化一个book; 
        errno = 0; // 专门用来记录错误的变量，本质是一个int
        FILE* temp = fopen(".\\library.dat", "r+");
        if (!temp)
        {
            printf("\t错误：无法打开library.dat，错误代码%d：%s\n\t", errno, strerror(errno));
            system("PAUSE");
            exit(0);
        }
        printf("\t现有如下书目\n");
        listBook();
        int i = 0, flag;
        int n = countBook();
        //循环加入书目 
        //输入需要添加的书本信息 
        printf("\t请按顺序输入书名,书籍类型,书目数量：（中间空格隔开）\n\t");
        do
        {
            flag = 1;
            scanf("%s %s %d", &ibook.name, &ibook.type, &ibook.num);
            for (i = 0;i < n;i++)
            {
                fread(&book, sizeof(Book), 1, temp);
                if (strcmp(ibook.name, book.name) == 0)
                {
                    printf("\t该图书已经存在,请重新输入:   \n\t");
                    break;
                }
                else
                {
                    flag = 0;
                }
            }
        } while (flag == 1);
        //将新书目写入
        if (fwrite(&ibook, sizeof(Book), 1, temp) != 1)
        {
            printf("\t无法保存该信息!\n");
            return;
        }
        else
        {
            printf("\t新图书信息已经保存!\n");
            n++;
        }
        fclose(temp);
        printf("\t添加该图书信息执行完毕!\n");
    }
    else  //如果不存在那就建立一个再进行add 
    {
        Book ibook;//用以添加额外书籍的变量ibook 
        Book book;// 初始化一个book; 
        errno = 0; // 专门用来记录错误的变量，本质是一个int
        FILE* temp = fopen(".\\library.dat", "a+");
        if (!temp) {
            printf("\t错误：无法打开library.dat，错误代码%d：%s\n\t", errno, strerror(errno));
            system("PAUSE");
            exit(0);
        }
        int i = 0, flag;
        int n = countBook();
        //循环加入书目 
        //输入需要添加的书本信息 
        printf("\t请按顺序输入书名,书籍类型,书目数量：（中间空格隔开）\n\t");
        scanf("%s %s %d", &ibook.name, &ibook.type, &ibook.num);
        if (fwrite(&ibook, sizeof(Book), 1, temp) != 1)
        {
            printf("\t无法保存该信息!\n\t");
            system("PAUSE");
            return;
        }
        fclose(temp);
        printf("\t添加该图书信息执行完毕!\n\t");
        system("PAUSE");
    }
}

void delBook() {
    // 该函数调用listBook()，随后接收用户的序号来删除书目
    FILE* fp, * temp;
    errno = 0;
    fp = fopen(".\\library.dat", "r+");
    if (!fp) {
        printf("\t错误：无法打开library.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    temp = fopen(".\\.library_temp.dat", "w+");
    if (!temp) {
        printf("\t错误：无法打开.library_temp.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    printf("\t现有如下书目\n");
    listBook();
    printf("\t请输入需要删除的书目序号以继续\n\t");
    int input, n = countBook();
    scanf("%d", &input);
    if (!(input >= 0 && input < n)) {
        printf("\t错误：输入的书目序号不合法\n");
        printf("\t返回中...\n\t");
        fclose(fp), fclose(temp);
        system("PAUSE");
        return;
    }
    fseek(fp, 0, SEEK_SET), fseek(temp, 0, SEEK_SET);
    Book book;
    for (int i = 0; i < n; i++) {
        fread(&book, sizeof(Book), 1, fp);
        if (i == input) continue;
        else fwrite(&book, sizeof(Book), 1, temp);
    }
    fclose(fp), fclose(temp);
    remove(".\\library.dat");
    if (rename(".\\.library_temp.dat", ".\\library.dat") == 0) {
        // 重命名成功
        printf("\t删除成功\n");
    }
    else {
        printf("\t错误：无法修改library_temp.dat为library.dat\n");
        printf("\t程序退出中...\n\t");
        system("PAUSE");
        exit(0);
    }
}

void editBook() {
    // 该函数调用listBook(), 随后接收用户的序号来修改书目
    FILE* fp, * temp;
    errno = 0;
    fp = fopen(".\\library.dat", "r+");
    if (!fp) {
        printf("\t错误：无法打开library.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    temp = fopen(".\\.library_temp.dat", "w+");
    if (!temp) {
        printf("\t错误：无法打开.library_temp.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    printf("\t现有如下书目\n");
    listBook();
    printf("\t请输入需要修改的书目序号以继续\n\t");
    int input, n = countBook();
    scanf("%d", &input);
    if (!(input >= 0 && input < n)) {
        printf("\t错误：输入的书目序号不合法\n");
        printf("\t返回中...\n\t");
        system("PAUSE");
        fclose(fp), fclose(temp);
        return;
    }
    Book edited;
    printf("\t请输入书目名称：\n\t");
    scanf("%s", edited.name);
    printf("\t请输入书目类型：\n\t");
    scanf("%s", edited.type);
    printf("\t请输入书目数量：\n\t");
    scanf("%d", &edited.num);
    fseek(fp, 0, SEEK_SET), fseek(temp, 0, SEEK_SET);
    Book book;
    for (int i = 0; i < n; i++) {
        fread(&book, sizeof(Book), 1, fp);
        if (i == input) fwrite(&edited, sizeof(Book), 1, temp);
        else fwrite(&book, sizeof(Book), 1, temp);
    }
    fclose(fp), fclose(temp);
    remove(".\\library.dat");
    if (rename(".\\.library_temp.dat", ".\\library.dat") == 0) {
        // 重命名成功
        printf("\t成功修改书名为：%s | 类型： %s | 数量：%d\n\t", edited.name, edited.type, edited.num);
        system("PAUSE");
    }
    else {
        printf("\t错误：无法修改.library_temp.dat为library.dat\n");
        printf("\t程序退出中...\n\t");
        system("PAUSE");
        exit(0);
    }
}
