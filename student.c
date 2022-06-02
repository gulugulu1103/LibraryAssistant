#include <stdio.h>
#include <string.h>
#include <time.h>
#include "class.h"
#include "library.h"
#include "menu.h"

int countStu() {
    // 该函数返回学生总数
    errno_t err; // 用来记录文件打开错误信息
    FILE* fp;
    if ((err = fopen(&fp, ".\\student.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开student.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    Stu stu;
    int cnt = 0;
    while (fread(&stu, sizeof(Stu), 1, fp) != EOF) {
        cnt++;
    }
    if (!feof(fp)) { // 未读到文末
        printf("\t软错误：文件无法读到文末\n");
    }
    fclose(fp);
    return cnt;
}

void addStu(char* num) {
    // 在"student.dat"中以追加模式新建以num为学号的学生
    errno_t err; // 用来记录文件打开错误信息
    FILE* fp;
    if ((err = fopen(&fp, ".\\student.dat", "a+")) != 0) { // failed to open the file
        printf("\t错误：无法打开student.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    Stu stu; // 初始化一个学生
    stu.oweNum = stu.recNum = 0;
    strcpy(stu.num, num);
    fwrite(&stu, sizeof(Stu), 1, fp);
    printf("\t成功添加学号为%s学生\n", stu.num);
    fclose(fp);
}

int searchStu(char* num) {
    // 在"student.dat"中查找以num为学号的学生，返回学生的顺位, 若没有找到则返回-1。
    int index = -1;
    errno_t err; // 用来记录文件打开错误信息
    FILE* fp;
    if ((err = fopen(&fp, ".\\student.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开student.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    fseek(fp, 0, SEEK_SET);
    Stu stu;
    int i = 0;
    while (fread(&stu, sizeof(Stu), 1, fp) != EOF) {
        if (strcmp(num, stu.num) == 0) { // 输入学号和学生学号一致
            index = i;
            break;
        }
        ++i;
    }
    if (!feof(fp)) { // 未读到文末
        printf("\t软错误：文件无法读到文末\n");
    }
    fclose(fp);
    return index;
}

void showStu(char* num) {
    // 调用searchStu()函数, 输出以num为学号的学生的近15条借阅记录
    errno_t err; // 用来记录文件打开错误信息
    FILE* fp;
    if ((err = fopen(&fp, ".\\student.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开student.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    Stu stu;
    int stuIndex = searchStu(num);
    if (stuIndex == -1) {
        printf("\t错误：找不到学号为%s的学生\n", num);
        printf("\t程序退出中...\n");
        fclose(fp);
        return;
    }
    fseek(fp, stuIndex * sizeof(Stu), SEEK_SET);
    fread(&stu, sizeof(Stu), 1, fp);
    Rec rec; // 记录
    for (int i = 0; i < stu.recNum; i++) {
        rec = stu.rec[i];
        printf("\t《%s》 | %s | %s\n", rec.book.name, rec.time, rec.borrow ? "借出":"归还");
    }
}

void borrowBook(char* num) {
    // 该函数调用library库中的listBook()函数，询问用户借阅书目的序号,修改library.dat与student.dat
    // 先检验学生是否能借书
    errno_t err; // 用来记录文件打开错误信息
    FILE* stufp;
    Stu stu;
    int stuIndex = searchStu(num);
    if (stuIndex == -1) {
        printf("\t错误：未找到该学生\n");
        printf("\t程序返回中...\n");
        return;
    }
    if ((err = fopen(&stufp, ".\\student.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开student.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    fseek(stufp, stuIndex * sizeof(Stu), SEEK_SET);
    fread(&stu, sizeof(Stu), 1, stufp);
    fclose(stufp);
    if (stu.oweNum >= 5) {
        // 该学生不可以借书
        printf("\t错误：你的借书数量已经达到最大上限，如需继续请先还书\n");
        printf("\t程序返回中...\n");
        return;
    }
    // 该学生可以借书，进入修改library.dat阶段
    printf("\t现有如下书目\n");
    listBook();
    printf("\t请输入借阅的书目序号\n");
    int destination;
    scanf("%d", &destination);
    FILE* libfp, * tempfp;
    if ((err = fopen(&libfp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开library.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    if ((err = fopen(&tempfp, ".\\.library_temp.dat", "w+")) != 0) { // failed to open the file
        printf("\t错误：无法打开library.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    fseek(libfp, 0, SEEK_SET), fseek(tempfp, 0, SEEK_SET);
    int n = countBook();
    Book book, bookFound;
    for (int i = 0; i < n; ++i) {
        fread(&book, sizeof(Book), 1, libfp);
        if (book.num <= 0) {
            --i;
            continue;
        }
        if (i == destination) {
            --book.num;
            stu.owe[stu.oweNum++] = bookFound = book;
            // 操作内存中的学生
        }
        fwrite(&book, sizeof(Book), 1, tempfp);
    }
    remove(".\\library.dat");
    if (rename(".\\.library_tmp.dat", ".\\library.dat") != 0) {
        printf("\t错误：无法修改.library_tmp.dat为library.dat\n");
        printf("\t程序退出中...\n");
        exit(0);
    }
    fclose(libfp), fclose(tempfp);
    // 构建记录，添加进stu
    time_t rawtime;
    time(&rawtime);
    Rec rec = { bookFound, ctime(&rawtime), 1 };
    stu.rec[stu.recNum++] = rec;
    while (stu.recNum >= 16) {
        // 让stu.recNum始终保持15条
        for (int i = 0; i < stu.recNum; ++i) {
            stu.rec[i] = stu.rec[i + 1];
        }
        --stu.recNum;
    }
    // 修改完成，进入修改student.dat阶段
    if ((err = fopen(&stufp, ".\\student.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开student.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    if ((err = fopen(&tempfp, ".\\.student_temp.dat", "w+")) != 0) { // failed to open the file
        printf("\t错误：无法打开.student_temp.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    n = countStu();
    Stu stutemp;
    for (int i = 0; i < n; ++i) {
        fread(&stutemp, sizeof(Stu), 1, stufp);
        if (i == stuIndex)
            fwrite(&stu, sizeof(Stu), 1, tempfp);
        else
            fwrite(&stutemp, sizeof(Stu), 1, tempfp);
    }
    remove(".\\student.dat");
    if (rename(".\\.student_tmp.dat", ".\\student.dat") == 0) {
        // 重命名成功
        printf("\t成功借阅书本：%s\n", bookFound.name);
    }
    else {
        printf("\t错误：无法修改.library_tmp.dat为library.dat\n");
        printf("\t程序退出中...\n");
        exit(0);
    }
}

void returnBook(char* num);
// 该函数会输出以num为学号未归还的书籍，让学生选择选项归还