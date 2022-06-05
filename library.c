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
        printf("\t������Ŀ���ȼ���Ŀ��\n\t"); 
        system("PAUSE");
        return;
    }
    else
    {
        errno = 0;
        FILE* fp = fopen(".\\library.dat", "r+");
        if (!fp) {
            printf("\t�����޷���library.dat���������%d��%s\n\t", errno, strerror(errno));
            system("PAUSE");
            exit(0);
        }
        printf("|**********************************************************************|\n");
        printf("\n\n");
        printf("\t%-16s%-10s%-6s\n", "����", "    ����","����");
        for (int i = 0; i < n; i++)
        {
            fread(&book, sizeof(Book), 1, fp);
            printf("\t%d | ��%-16s�� | %-10s | %-6d\n", number, book.name, book.type, book.num);
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
    int a = access(".\\.library.dat", F_OK);//access���������ж��ļ��Ƿ���� 
    if (a == 0)//�ļ�����,ֱ�ӽ���add���� 
    {
        Book ibook;//������Ӷ����鼮�ı���ibook 
        Book book;// ��ʼ��һ��book; 
        errno = 0; // ר��������¼����ı�����������һ��int
        FILE* temp = fopen(".\\library.dat", "r+");
        if (!temp)
        {
            printf("\t�����޷���library.dat���������%d��%s\n\t", errno, strerror(errno));
            system("PAUSE");
            exit(0);
        }
        printf("\t����������Ŀ\n");
        listBook();
        int i = 0, flag;
        int n = countBook();
        //ѭ��������Ŀ 
        //������Ҫ��ӵ��鱾��Ϣ 
        printf("\t�밴˳����������,�鼮����,��Ŀ���������м�ո������\n\t");
        do
        {
            flag = 1;
            scanf("%s %s %d", &ibook.name, &ibook.type, &ibook.num);
            for (i = 0;i < n;i++)
            {
                fread(&book, sizeof(Book), 1, temp);
                if (strcmp(ibook.name, book.name) == 0)
                {
                    printf("\t��ͼ���Ѿ�����,����������:   \n\t");
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
            return;
        }
        else
        {
            printf("\t��ͼ����Ϣ�Ѿ�����!\n");
            n++;
        }
        fclose(temp);
        printf("\t��Ӹ�ͼ����Ϣִ�����!\n");
    }
    else  //����������Ǿͽ���һ���ٽ���add 
    {
        Book ibook;//������Ӷ����鼮�ı���ibook 
        Book book;// ��ʼ��һ��book; 
        errno = 0; // ר��������¼����ı�����������һ��int
        FILE* temp = fopen(".\\library.dat", "a+");
        if (!temp) {
            printf("\t�����޷���library.dat���������%d��%s\n\t", errno, strerror(errno));
            system("PAUSE");
            exit(0);
        }
        int i = 0, flag;
        int n = countBook();
        //ѭ��������Ŀ 
        //������Ҫ��ӵ��鱾��Ϣ 
        printf("\t�밴˳����������,�鼮����,��Ŀ���������м�ո������\n\t");
        scanf("%s %s %d", &ibook.name, &ibook.type, &ibook.num);
        if (fwrite(&ibook, sizeof(Book), 1, temp) != 1)
        {
            printf("\t�޷��������Ϣ!\n\t");
            system("PAUSE");
            return;
        }
        fclose(temp);
        printf("\t��Ӹ�ͼ����Ϣִ�����!\n\t");
        system("PAUSE");
    }
}

void delBook() {
    // �ú�������listBook()���������û��������ɾ����Ŀ
    FILE* fp, * temp;
    errno = 0;
    fp = fopen(".\\library.dat", "r+");
    if (!fp) {
        printf("\t�����޷���library.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    temp = fopen(".\\.library_temp.dat", "w+");
    if (!temp) {
        printf("\t�����޷���.library_temp.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    printf("\t����������Ŀ\n");
    listBook();
    printf("\t��������Ҫɾ������Ŀ����Լ���\n\t");
    int input, n = countBook();
    scanf("%d", &input);
    if (!(input >= 0 && input < n)) {
        printf("\t�����������Ŀ��Ų��Ϸ�\n");
        printf("\t������...\n\t");
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
        // �������ɹ�
        printf("\tɾ���ɹ�\n");
    }
    else {
        printf("\t�����޷��޸�library_temp.datΪlibrary.dat\n");
        printf("\t�����˳���...\n\t");
        system("PAUSE");
        exit(0);
    }
}

void editBook() {
    // �ú�������listBook(), �������û���������޸���Ŀ
    FILE* fp, * temp;
    errno = 0;
    fp = fopen(".\\library.dat", "r+");
    if (!fp) {
        printf("\t�����޷���library.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    temp = fopen(".\\.library_temp.dat", "w+");
    if (!temp) {
        printf("\t�����޷���.library_temp.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    printf("\t����������Ŀ\n");
    listBook();
    printf("\t��������Ҫ�޸ĵ���Ŀ����Լ���\n\t");
    int input, n = countBook();
    scanf("%d", &input);
    if (!(input >= 0 && input < n)) {
        printf("\t�����������Ŀ��Ų��Ϸ�\n");
        printf("\t������...\n\t");
        system("PAUSE");
        fclose(fp), fclose(temp);
        return;
    }
    Book edited;
    printf("\t��������Ŀ���ƣ�\n\t");
    scanf("%s", edited.name);
    printf("\t��������Ŀ���ͣ�\n\t");
    scanf("%s", edited.type);
    printf("\t��������Ŀ������\n\t");
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
        // �������ɹ�
        printf("\t�ɹ��޸�����Ϊ��%s | ���ͣ� %s | ������%d\n\t", edited.name, edited.type, edited.num);
        system("PAUSE");
    }
    else {
        printf("\t�����޷��޸�.library_temp.datΪlibrary.dat\n");
        printf("\t�����˳���...\n\t");
        system("PAUSE");
        exit(0);
    }
}
