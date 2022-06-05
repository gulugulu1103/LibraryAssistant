#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "class.h"
#include "library.h"
#include "menu.h"
#include "student.h"

int countStu() {
    // �ú�������ѧ������
    errno = 0; // ������¼�ļ��򿪴�����Ϣ
    FILE* fp = fopen(".\\student.dat", "r+");
    if (!fp) {
        if (errno == 2) {
            return 0;
        }
        printf("\t�����޷���student.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    Stu stu;
    int cnt = 0;
    fseek(fp, 0, SEEK_SET);
    while (!feof(fp)) { // δ������ĩ
        fread(&stu, sizeof(Stu), 1, fp);
        cnt++;
    }
    fclose(fp);
    return cnt;
}

int searchStu(char* num) {
    // ��"student.dat"�в�����numΪѧ�ŵ�ѧ��������ѧ����˳λ, ��û���ҵ��򷵻�-1��
    if (countStu() == 0) {
        return -1;
    }
    int index = -1;
    errno = 0; // ������¼�ļ��򿪴�����Ϣ
    FILE* fp = fopen(".\\student.dat", "r+");
    if (!fp) {
        if (errno == 2) {
            printf("\tû��student.dat�ļ������ȴ���ѧ��\n\t");
            errno = 0; // ����ָ���־
            system("PAUSE");
            return -1;
        }
        printf("\t�����޷���student.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    Stu stu;
    int i = 0;
    fseek(fp, 0, SEEK_SET);
    while (!feof(fp)) {
        fread(&stu, sizeof(Stu), 1, fp);
        if (strcmp(num, stu.num) == 0) { // ����ѧ�ź�ѧ��ѧ��һ��
            index = i;
            break;
        }
        ++i;
    }
    fclose(fp);
    return index;
}

void addStu(char* num) {
    // ��"student.dat"����׷��ģʽ�½���numΪѧ�ŵ�ѧ��
    if (searchStu(num) > -1) {
        printf("\t���󣺸�ѧ���Ѵ���\n\t");
        system("PAUSE");
        return;
    }
    errno = 0; // ������¼�ļ��򿪴�����Ϣ
    FILE* fp = fopen(".\\student.dat", "a+");
    if (!fp) {
        if (errno != 2) {
            printf("\t�����޷���student.dat���������%d��%s\n\t", errno, strerror(errno));
            system("PAUSE");
            exit(0);
        }
    }
    Stu stu; // ��ʼ��һ��ѧ��
    stu.oweNum = stu.recNum = 0;
    Book book;
    Rec rec;
    for (int i = 0; i < 21; i++) {
        stu.owe[i] = book;
        stu.rec[i] = rec;
    }
    strcpy(stu.num, num);
    fwrite(&stu, sizeof(Stu), 1, fp);
    printf("\t�ɹ����ѧ��Ϊ%sѧ��\n\t", stu.num);
    system("PAUSE");
    fclose(fp);
}

void showStu(char* num) {
    // ����searchStu()����, �����numΪѧ�ŵ�ѧ���Ľ�15�����ļ�¼
    errno = 0; // ������¼�ļ��򿪴�����Ϣ
    FILE* fp = fopen(".\\student.dat", "r+");
    if (!fp) {
        if (errno == 2) {
            printf("\tû��student.dat�ļ������ȴ���ѧ��\n\t");
            errno = 0; // ����ָ���־
            system("PAUSE");
            return;
        }
        printf("\t�����޷���student.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    Stu stu;
    int stuIndex = searchStu(num);
    if (stuIndex == -1) {
        printf("\t�����Ҳ���ѧ��Ϊ%s��ѧ��\n\t", num);
        printf("\t�����˳���...\n");
        fclose(fp);
        system("PAUSE");
        return;
    }
    fseek(fp, stuIndex * sizeof(Stu), SEEK_SET);
    fread(&stu, sizeof(Stu), 1, fp);
    if (!stu.recNum) {
        printf("\t����û�н��ļ�¼\n\t");
        system("PAUSE");
        return;
    }
    Rec rec; // ��¼
    for (int i = 0; i < stu.recNum; i++) {
        rec = stu.rec[i];
        printf("\t %d | ��%s�� | %s | %s\n", i, \
        rec.book.name, rec.time, (rec.borrow ? "�� �� ":"�黹"));
    }
}

void borrowBook(char* num) {
    // �ú�������library���е�listBook()������ѯ���û�������Ŀ�����,�޸�library.dat��student.dat
    // �ȼ���ѧ���Ƿ��ܽ���
    errno = 0; // ������¼�ļ��򿪴�����Ϣ
    int n = countBook();
    if (n == 0) {
        printf("\t����û����Ŀ��Ϣ������ϵ����Ա�����Ŀ��Ϣ\n\t");
        system("PAUSE");
        return;
    }
    FILE* libfp, * tempfp, * stufp;
    Stu stu;
    int stuIndex = searchStu(num);
    if (stuIndex == -1) {
        printf("\t����δ�ҵ���ѧ��\n");
        printf("\t���򷵻���...\n\t");
        system("PAUSE");
        return;
    }
    stufp = fopen(".\\student.dat", "r+");
    if (!stufp) {
        if (errno == 2) {
            printf("\tû��student.dat�ļ������ȴ���ѧ��\n\t");
            errno = 0; // ����ָ���־
            system("PAUSE");
            return;
        }
        printf("\t�����޷���student.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    fseek(stufp, stuIndex * sizeof(Stu), SEEK_SET);
    fread(&stu, sizeof(Stu), 1, stufp);
    fclose(stufp);
    if (stu.oweNum >= 5) {
        // ��ѧ�������Խ���
        printf("\t������Ľ��������Ѿ��ﵽ������ޣ�����������Ȼ���\n");
        printf("\t���򷵻���...\n\t");
        system("PAUSE");
        return;
    }
    // ��ѧ�����Խ��飬�г��鼮��ѯ������ĵ��鼮
    printf("\t����������Ŀ\n");
    listBook();
    printf("\t��������ĵ���Ŀ���\n\t");
    int destination;
    scanf("%d", &destination);
    if (destination < 0 || destination >= countBook()) {
        printf("\t���������˴������Ŀ���\n");
        printf("\t���򷵻���...\n\t");
        system("PAUSE");
        return;
    }
    // �����鼮�Ƿ��п��(��book.num > 0)
    libfp = fopen(".\\library.dat", "r+");
    if (!libfp) {
        if (errno == 2) {
            printf("\tû��library.dat�ļ�������¼���鼮\n\t");
            errno = 0; // ����ָ���־
            system("PAUSE");
            return;
        }
        printf("\t�����޷���library.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    fseek(libfp, destination * sizeof(Book), SEEK_SET);
    Book book, bookFound; //book���ڱ���library.dat��bookFound���ڼ�¼�����ļ�¼��
    fread(&bookFound, sizeof(Book), 1, libfp);
    fclose(libfp);
    if (bookFound.num <= 0) { // bookFound.num ������-1
        printf("\t���󣺸���Ŀ���ɽ��ģ���Ϊ������Ϊ0\n");
        printf("\t���򷵻���...\n\t");
        system("PAUSE");
        return;
    }
    // �Ѿ�ѡ��Ŀ����Ŀ�������޸�library.dat�׶Σ�����ѡ��Ŀ����-1
    libfp = fopen(".\\library.dat", "r+");
    if (!libfp) {
        if (errno == 2) {
            printf("\tû��library.dat�ļ������ȴ���ѧ��\n\t");
            errno = 0; // ����ָ���־
            system("PAUSE");
            return;
        }
        printf("\t�����޷���library.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    tempfp = fopen(".\\.library_temp.dat", "w+");
    if (!tempfp) {
        printf("\t�����޷���.library_temp.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    fseek(libfp, 0, SEEK_SET), fseek(tempfp, 0, SEEK_SET);
    for (int i = 0; i < n; ++i) {
        fread(&book, sizeof(Book), 1, libfp);
        if (i == destination) {
            --bookFound.num;
            stu.owe[stu.oweNum++] = bookFound; // �޸��ڴ��е�ѧ������owe��������Ӹ�book
            fwrite(&bookFound, sizeof(Book), 1, tempfp);
        }
        else {
            fwrite(&book, sizeof(Book), 1, tempfp);
        }
    }
    fclose(libfp), fclose(tempfp);
    remove(".\\library.dat");
    if (rename(".\\.library_temp.dat", ".\\library.dat") == -1) {
        printf("errno = %d\n: %s", errno, strerror(errno));
        printf("\t�����޷��޸�.library_temp.datΪlibrary.dat\n");
        printf("\t�����˳���...\n\t");
        system("PAUSE");
        exit(0);
    }
    // ������¼rec����ӽ�stu�Ľ軹����
    time_t rawtime;
    time(&rawtime);
    // Rec rec = { bookFound, ctime(&rawtime), 1 };
    Rec rec;
    rec.book = bookFound;
    rec.borrow = 1;
    strcpy(rec.time, ctime(&rawtime));
    stu.rec[stu.recNum++] = rec;
    while (stu.recNum >= 16) {
        // ��stu.recNumʼ�ձ���15��
        for (int i = 0; i < stu.recNum; ++i) {
            stu.rec[i] = stu.rec[i + 1];
        }
        --stu.recNum;
    }
    // �޸��ڴ�stu��ɣ������޸�student.dat�׶�
    stufp = fopen(".\\student.dat", "r+");
    if (!stufp) {
        if (errno == 2) {
            printf("\tû��student.dat�ļ������ȴ���ѧ��\n\t");
            errno = 0; // ����ָ���־
            system("PAUSE");
            return;
        }
        printf("\t�����޷���student.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    tempfp = fopen(".\\.student_temp.dat", "w+");
    if (!tempfp) {
        printf("\t�����޷���.student_temp.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    fseek(stufp, 0, SEEK_SET), fseek(tempfp, 0, SEEK_SET);
    n = countStu();
    Stu stutemp;
    for (int i = 0; i < n; ++i) {
        fread(&stutemp, sizeof(Stu), 1, stufp);
        if (i == stuIndex)
            fwrite(&stu, sizeof(Stu), 1, tempfp);
        //��Ϊд��libraryʱ�Ѿ��޸Ĺ��˽軹����������ֱ��д��
        else
            fwrite(&stutemp, sizeof(Stu), 1, tempfp);
    }
    fclose(tempfp), fclose(libfp), fclose(stufp);
    remove(".\\student.dat");
    if (rename(".\\.student_temp.dat", ".\\student.dat") == 0) {
        // �������ɹ�
        printf("\t�ɹ������鱾��%s\n\t", bookFound.name);
        system("PAUSE");
    }
    else {
        printf("\t�����޷��޸�.library_temp.datΪlibrary.dat\n");
        printf("\t�����˳���...\n\t");
        system("PAUSE");
        exit(0);
    }
}

void returnBook(char* num) {
    // �ú����������numΪѧ��δ�黹���鼮����ѧ��ѡ��ѡ��黹
    errno = 0; // ������¼�ļ��򿪴�����Ϣ
    FILE* stufp, * tempfp, * libfp;
    Stu stu;
    int stuIndex = searchStu(num);
    if (stuIndex == -1) {
        printf("\t����δ�ҵ���ѧ��\n");
        printf("\t���򷵻���...\n\t");
        system("PAUSE");
        return;
    }
    stufp = fopen(".\\student.dat", "r+");
    if (!stufp) {
        if (errno == 2) {
            printf("\tû��student.dat�ļ������ȴ���ѧ��\n\t");
            errno = 0; // ����ָ���־
            system("PAUSE");
            return;
        }
        printf("\t�����޷���student.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    fseek(stufp, stuIndex * sizeof(Stu), SEEK_SET);
    fread(&stu, sizeof(Stu), 1, stufp);
    fclose(stufp);
    if (stu.oweNum == 0) {
        // ��ѧ�������Խ���
        printf("\t������Ľ����б�Ϊ�գ�����������Ƚ���\n");
        printf("\t���򷵻���...\n\t");
        system("PAUSE");
        return;
    }
    // ��ѧ�����Ի��飬�����޸�ѧ��δ����Ŀ�׶�
    printf("\t������Ŀ��δ�黹\n");
    for (int i = 0; i < stu.oweNum; i++) {
        printf("\t %d  | ��%s��\n", i, stu.owe[i].name);
    }
    printf("\t������黹����Ŀ���\n\t");
    int destination;
    scanf("%d", &destination);
    // ����destination�Ƿ�Ϸ�
    if (destination < 0 || destination >= stu.oweNum) {
        printf("\t��������Ĺ黹��Ŀ��Ų��Ϸ�\n");
        printf("\t�����˳���...\n\t");
        system("PAUSE");
        return;
    }
    for (int i = destination; i < stu.oweNum - 1; i++) {
        stu.owe[i] = stu.owe[i + 1];
    }
    stu.oweNum--;
    // �޸�library.dat, �����鼮��+1
    libfp = fopen(".\\library.dat", "r+");
    if (!libfp) {
        if (errno == 2) {
            printf("\tû��library.dat�ļ������ȴ���ѧ��\n\t");
            errno = 0; // ����ָ���־
            system("PAUSE");
            return;
        }
        printf("\t�����޷���library.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    tempfp = fopen(".\\.library_temp.dat", "w+");
    if (!tempfp) {
        printf("\t�����޷���.library_temp.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    fseek(libfp, 0, SEEK_SET), fseek(tempfp, 0, SEEK_SET);
    int n = countBook();
    Book book, bookFound; //book���ڱ���library.dat��bookFound���ڼ�¼�����ļ�¼��
    for (int i = 0; i < n; ++i) {
        fread(&book, sizeof(Book), 1, libfp);
        if (i == destination) {
            ++book.num;
            bookFound = book;
        }
        fwrite(&book, sizeof(Book), 1, tempfp);
    }
    fclose(libfp), fclose(tempfp), fclose(stufp);
    remove(".\\library.dat");
    if (rename(".\\.library_temp.dat", ".\\library.dat") == -1) {
        printf("errno = %d\n: %s", errno, strerror(errno));
        printf("\t�����޷��޸�.library_temp.datΪlibrary.dat\n");
        printf("\t�����˳���...\n\t");
        system("PAUSE");
        exit(0);
    }
    // ������¼����ӽ�stu
    time_t rawtime;
    time(&rawtime);
    // Rec rec = { bookFound, ctime(&rawtime), 1 };
    Rec rec;
    rec.book = bookFound;
    rec.borrow = 0;
    strcpy(rec.time, ctime(&rawtime));
    stu.rec[stu.recNum++] = rec;
    while (stu.recNum >= 16) {
        // ��stu.recNumʼ�ձ���15��
        for (int i = 0; i < stu.recNum; ++i) {
            stu.rec[i] = stu.rec[i + 1];
        }
        --stu.recNum;
    }
    // �޸���ɣ������޸�student.dat�׶�
    stufp = fopen(".\\student.dat", "r+");
    if (!stufp) {
        if (errno == 2) {
            printf("\tû��student.dat�ļ������ȴ���ѧ��\n\t");
            errno = 0; // ����ָ���־
            system("PAUSE");
            return;
        }
        printf("errno = %d\n: %s", errno, strerror(errno));
        printf("\t�����޷���student.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    tempfp = fopen(".\\.student_temp.dat", "w+");
    if (!tempfp) {
        printf("errno = %d\n: %s", errno, strerror(errno));
        printf("\t�����޷���.student_temp.dat���������%d��%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    n = countStu();
    Stu stutemp;
    for (int i = 0; i < n; ++i) {
        fread(&stutemp, sizeof(Stu), 1, stufp);
        if (i == stuIndex)
            fwrite(&stu, sizeof(Stu), 1, tempfp);
        //��Ϊд��libraryʱ�Ѿ��޸Ĺ��˽軹����������ֱ��д��
        else
            fwrite(&stutemp, sizeof(Stu), 1, tempfp);
    }
    fclose(tempfp), fclose(libfp), fclose(stufp);
    remove(".\\student.dat");
    if (rename(".\\.student_temp.dat", ".\\student.dat") == 0) {
        // �������ɹ�
        printf("\t�ɹ������鱾��%s\n\t", bookFound.name);
        system("PAUSE");
    }
    else {
        printf("\t�����޷��޸�.library_temp.datΪlibrary.dat\n");
        printf("\t�����˳���...\n");
        system("PAUSE");
        exit(0);
    }
}
