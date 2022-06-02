#include <stdlib.h>
#include <stdio.h>
#include "class.h"
void addBook()
{
	FILE * temp;
	char Flag;
	Book book[1000];
	Book ibook[1000]; 
    errno_t err; // ר��������¼����ı�����������һ��int
    if ((err = fopen_s(&temp,".\\.library_temp.dat", "w+")) != 0) { // failed to open the file
        printf("\t�����޷���.library_temp.dat���������%d\n", err);
        printf("\t�����˳���...\n");
        exit(0);
    }
    printf("\t����������Ŀ\n");
    listBook();
    printf("��ѡ���Ƿ�����鱾��Ϣ(y/n):");
    Flag = getchar();
    if (Flag == 'n')
	{
		return 0;
		fclose(temp);
	}
	int i = 0,flag;
	int n = countBook();
	//ѭ��������Ŀ 
	while (Flag == 'y')
	{ 
		//ͼ���Ų����ظ�
		printf("������ͼ����:  ");
		do
		{
			Flag = 0;
			scanf("%d", &ibook[n-1].num);
			for (i = 0; i < n; i++)
			{
				if (book[i].num == ibook[n-1].num)
				{
					flag = 1;
					printf("��ͼ�����Ѿ�����,����������:   ");
					break;
				}
			}
		} while (flag == 1);
	
		printf("������ͼ������:");
		scanf("%s", ibook[n-1].name);
		printf("������ͼ������:");
		scanf("%s", ibook[n-1].type);
		
		//������Ŀд��
		if (fwrite(&ibook[n-1], sizeof(Book), 1, temp) != 1)
		{
			printf("�޷��������Ϣ!\n");
			return 0;
		}
		else
		{
			printf("%d��ͼ����Ϣ�Ѿ�����!\n", ibook[n-1].num);
			n++;
		}
		printf("����������Ϣ��?(y/n)");
		Flag = getchar();
	}
	fclose(temp);
	printf("���ͼ����Ϣִ�����!\n");
}
void listBook()
{
	FILE *fp;
	errno_t err;
    if ((err = fopen_s(&fp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t�����޷���library.dat���������%d\n", err);
        printf("\t�����˳���...\n");
        exit(0);
    }
    int i, record;
    Book book[i];
    record = countBook();
    if (record <= 0)
    {
    	printf ("��ǰͼ�����ȱ���鼮�����������Ŀ")�� 
	}
	else
	{ 
		
		printf("|**********************************************************************|\n");
		printf("\n\n");
		printf("\t%-6s%-16s%-10s\n", "���", "����", "����");
    	for (i = 0;i < record;i++)
    	{
    		printf("%-6d%-16s%-10s\n",book[i].num,book[i].name,book[i].type);
		}
		printf("\n\n");
		printf("|**********************************************************************|\n");
		printf("\n\n");

	}	
	return 0; 
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
