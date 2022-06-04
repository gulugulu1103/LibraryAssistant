#include <stdlib.h>
#include <stdio.h>
#include "class.h"
void addBook()
{
	FILE * temp;
	Book ibook;//用以添加额外书籍的变量ibook 
	Book book;// 初始化一个book; 
    errno_t err; // 专门用来记录错误的变量，本质是一个int
    if ((err = fopen_s(&temp,".\\.library_temp.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开.library_temp.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    printf("\t现有如下书目\n");
    listBook();
	int i = 0,flag;
	int n = countBook();
	//循环加入书目 
	//输入需要添加的书本信息 
	printf("\t请按顺序输入书名,书籍类型,书目数量：（中间空格隔开）\n");
	do
	{
		flag = 1;
		scanf("%s %s %d", &ibook.name, &ibook.type, &ibook.num);
		for (i = 0;i < n;i++)
		{
			fread(&book,sizeof(Book),1,temp);
			if (strcmp(ibook.name,book.name) == 0)
			{
				printf("\t该图书已经存在,请重新输入:   ");
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
		return 0;
	}
	else
	{
		printf("\t新图书信息已经保存!\n");
		n++;
	}
	fclose(temp);
	printf("\t添加该图书信息执行完毕!\n");
}
void listBook()
{
	FILE *fp;
	errno_t err;
    if ((err = fopen_s(&fp, ".\\library.dat", "r+")) != 0) 
	{ 
		// failed to open the file
        printf("\t错误：无法打开library.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    int i,number = 0,n;
    n = countBook();
    Book book;
    if(n == 0)
	{
		printf("暂时无书目记录，请先添加书目！"); 
	} 
	else
	{
		printf("\t|**********************************************************************|\n");
		printf("\n\n");
		printf("\t%-16s%-10s%-6d\n", "书名", "类型","数量");
	   	for (int i = 0; i < n; i++) 
		{
        	fread(&book, sizeof(Book), 1, fp);
	   		printf("\t%d%-16s%-10s%-6d\n",number,book.name,book.type,book.num);
	   		number++;
		}
		printf("\n\n");
		printf("\t|**********************************************************************|\n");
		printf("\n\n");
	}
	fclose(fp); 
	return 0; 
}
int  countBook()
{
	int record = 0;
	Book book;
	FILE *fp;
	errno_t err;
    if ((err = fopen_s(&fp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开library.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
	while(!feof(fp))
	{
		fread(&book,sizeof(Book),1,fp);
		record++;
	}
	fclose(fp);
	return record; 
}

void delBook() {
    // 该函数调用listBook()，随后接收用户的序号来删除书目
    FILE* fp, * temp;
    errno_t err; // 专门用来记录错误的变量，本质是一个int
    if ((err = fopen_s(&fp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开library.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    if ((err = fopen_s(&temp, ".\\.library_temp.dat", "w+")) != 0) { // failed to open the file
        printf("\t错误：无法打开.library_temp.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    printf("\t现有如下书目\n");
    listBook();
    printf("\t请输入需要删除的书目序号以继续\n");
    int input, n = countBook();
    scanf("%d", &input);
    if (!(input >= 0 && input < n)) {
        printf("\t错误：输入的书目序号不合法\n");
        printf("\t返回中...\n");
        fclose(fp), fclose(temp);
        return;
    }
    fseek(fp, 0, SEEK_SET), fseek(temp, 0, SEEK_SET);
    Book book;
    for (int i = 0; i < n; i++) {
        fread(&book, sizeof(Book), 1, fp);
        if (i == input) continue;
        else fwrite(&book, sizeof(Book), 1, temp);
    }
    remove(".\\library.dat");
    if (rename(".\\.library_tmp.dat", ".\\library.dat") == 0) {
        // 重命名成功
        printf("\t删除成功\n");
    }
    else {
        printf("\t错误：无法修改library_tmp.dat为library.dat\n");
        printf("\t程序退出中...\n");
        fclose(fp), fclose(temp);
        exit(0);
    }
}

void editBook() {
    // 该函数调用listBook(), 随后接收用户的序号来修改书目
    FILE* fp, * temp;
    errno_t err; // 用来记录
    if ((err = fopen_s(&fp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开library.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    if ((err = fopen_s(&temp, ".\\.library_temp.dat", "w+")) != 0) { // failed to open the file
        printf("\t错误：无法打开.library_temp.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    printf("\t现有如下书目\n");
    listBook();
    printf("\t请输入需要修改的书目序号以继续\n");
    int input, n = countBook();
    scanf("%d", &input);
    if (!(input >= 0 && input < n)) {
        printf("\t错误：输入的书目序号不合法\n");
        printf("返回中...");
        fclose(fp), fclose(temp);
        return;
    }
    Book edited;
    printf("\t请输入书目名称：\n");
    scanf("%s", edited.name);
    printf("\t请输入书目类型：\n");
    scanf("%s", edited.type);
    fseek(fp, 0, SEEK_SET), fseek(temp, 0, SEEK_SET);
    Book book;
    for (int i = 0; i < n; i++) {
        fread(&book, sizeof(Book), 1, fp);
        if (i == input) fwrite(&edited, sizeof(Book), 1, temp);
        else fwrite(&book, sizeof(Book), 1, temp);
    }
    remove(".\\library.dat");
    if (rename(".\\.library_tmp.dat", ".\\library.dat") == 0) {
        // 重命名成功
        printf("\t成功修改书名为：%s\n", edited.name);
    }
    else {
        printf("\t错误：无法修改.library_tmp.dat为library.dat\n");
        printf("\t程序退出中...\n");
        exit(0);
    }
}