 #include <stdlib.h>
#include <stdio.h>
#include "class.h"
void addBook()
{
	FILE * temp;
	char Flag;
	Book ibook;//������Ӷ����鼮�ı���ibook 
	Book book;// ��ʼ��һ��book; 
    errno_t err; // ר��������¼����ı�����������һ��int
    if ((err = fopen_s(&temp,".\\.library_temp.dat", "a+")) != 0) { // failed to open the file
        printf("\t�����޷���.library_temp.dat���������%d\n", err);
        printf("\t�����˳���...\n");
        exit(0);
    }
    printf("\t����������Ŀ\n");
    listBook();
    printf("\t��ѡ���Ƿ�����鱾��Ϣ(y/n):");
    Flag = getchar();
    if (Flag == 'n')
	{
		fclose(temp);
		exit(0); 
	}
	int i = 0,flag;
	int n = countBook();
	//ѭ��������Ŀ 
	while (Flag == 'y')
	{ 
		//������Ҫ��ӵ��鱾��Ϣ 
		printf("\t�밴˳�������������鼮���ͣ����м�ո������\n");
		do
		{
			flag = 1;
			scanf("%s %s", &ibook.name, &ibook.type);
			for (fread(&book, sizeof(Book), 1, temp) != EOF)
			{
				if (strcmp(ibook.name,book.name) == 0)
				{
					printf("\t��ͼ���Ѿ�����,����������:   ");
					break;
				}
				else
				{
					flag = 0;
				} 
			}
		} while (flag == 1);
		//������Ŀд��
		if (fwrite(&ibook, sizeof(Book), 1, temp) != 1)
		{
			printf("\t�޷��������Ϣ!\n");
			return 0;
		}
		else
		{
			printf("\t��ͼ����Ϣ�Ѿ�����!\n");
			n++;
		}
		printf("\t����������Ϣ��?(y/n)");
		Flag = getchar();
	}
	fclose(temp);
	printf("\t��Ӹ�ͼ����Ϣִ�����!\n");
}
void listBook()
{
	FILE *fp;
	errno_t err;
    if ((err = fopen_s(&fp, ".\\library.dat", "r+")) != 0) 
	{ 
		// failed to open the file
        printf("\t�����޷���library.dat���������%d\n", err);
        printf("\t�����˳���...\n");
        exit(0);
    }
    int i,number = 0;
    Book book;
    if (record <= 0)
    {
    	printf ("\t��ǰͼ�����ȱ���鼮�����������Ŀ");
	}
	else
	{ 
		
		printf("\t|**********************************************************************|\n");
		printf("\n\n");
		printf("\t%-16s%-10s\n", "����", "����");
    	for (fread(&book, sizeof(Book), 1, fp) != EOF)
    	{
    		printf("\t%d%-16s%-10s\n",number,book.name,book.type);
    		number++;
		}
		printf("\n\n");
		printf("\t|**********************************************************************|\n");
		printf("\n\n");

	}	
	return 0; 
}
int  countBook()
{
	int record = 0;
	Book book;
	FILE *fp;
	errno_t err;
    if ((err = fopen_s(&fp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t�����޷���library.dat���������%d\n", err);
        printf("\t�����˳���...\n");
        exit(0);
    }
    while (fread(&book, sizeof(Book), 1, fp) != EOF)
	{
			record++;
	}
	if (!feof(fp))
	{
		printf("\tδ�ܹ�������ĩ"); 
	}
	fclose(fp);
	return record; 
}
void delBook() {
    // 该函数调用listBook()，随后接收用户的序号来删除书目
    FILE* fp, * temp;
    errno_t err; // 专门用来记录错误的变量，本质是一个int
    if ((err = fopen(&fp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开library.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    if ((err = fopen(&temp, ".\\.library_temp.dat", "w+")) != 0) { // failed to open the file
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
    if ((err = fopen(&fp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开library.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    if ((err = fopen(&temp, ".\\.library_temp.dat", "w+")) != 0) { // failed to open the file
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
