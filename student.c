#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "class.h"
#include "library.h"
#include "menu.h"

int countStu() {
    // 该函数返回学生总数
    errno err; // 用来记录文件打开错误信息
    FILE* fp;
    if ((err = fopen_s(&fp, ".\\student.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开student.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    Stu stu;
    int cnt = 0;
    fseek(fp, 0, SEEK_SET);
    while (!feof(fp)) { // 未读到文末
        fread(&stu, sizeof(Stu), 1, fp);
        cnt++;
    }
    fclose(fp);
    return cnt;
}

void addStu(char* num) {
    // 在"student.dat"中以追加模式新建以num为学号的学生
    errno err; // 用来记录文件打开错误信息
    FILE* fp;
    if ((err = fopen_s(&fp, ".\\student.dat", "a+")) != 0) { // failed to open the file
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
    errno err; // 用来记录文件打开错误信息
    FILE* fp;
    if ((err = fopen_s(&fp, ".\\student.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开student.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    Stu stu;
    int i = 0;
    fseek(fp, 0, SEEK_SET);
    while (!feof(fp)) {
        fread(&stu, sizeof(Stu), 1, fp);
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
    errno err; // 用来记录文件打开错误信息
    FILE* fp;
    if ((err = fopen_s(&fp, ".\\student.dat", "r+")) != 0) { // failed to open the file
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
        printf("\t %d | 《%s》 | %s | %s\n", i, rec.book.name, rec.time, rec.borro ?  "       借出":"归还");
    }
}

void borrowBook(char* num) {
    // 该函数调用library库中的listBook()函数，询问用户借阅书目的序号,修改library.dat与student.dat
    // 先检验学生是否能借书
    errno err; // 用来记录文件打开错误信息
    FILE* stufp;
    Stu stu;
    int stuIndex = searchStu(num);
    if (stuIndex == -1) {
        printf("\t错误：未找到该学生\n");
        printf("\t程序返回中...\n");
        return;
    }
    if ((err = fopen_s(&stufp, ".\\student.dat", "r+")) != 0) { // failed to open the file
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
    // 该学生可以借书，列出书籍，询问想借阅的书籍
    printf("\t现有如下书目\n");
    listBook();
    printf("\t请输入借阅的书目序号\n");
    FILE* libfp, * tempfp;
    int destination;
    scanf("%d", &destination);
    if (destination < 0 || destination >= countBook()) {
        printf("\t错误：输入了错误的书目序号\n");
        printf("\t程序返回中\n");
        return;
    }
    // 检测该书籍是否还有库存(即book.num > 0)
    if ((err = fopen_s(&libfp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开library.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    fseek(libfp, destination * sizeof(Book), SEEK_SET);
    Book book, bookFound; //book用于遍历library.dat，bookFound用于记录到借阅记录中
    fread(&bookFound, sizeof(Book), 1, libfp);
    fclose(libfp);
    if (bookFound.num <= 0) { // bookFound.num 不可以-1
        printf("错误：该书目不可借阅，因为其数量为0");
        printf("\t程序返回中...\n");
        return;
    }
    // 已经选择目标书目，进入修改library.dat阶段，让所选书目数量-1
    if ((err = fopen_s(&libfp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开library.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    if ((err = fopen_s(&tempfp, ".\\.library_temp.dat", "w+")) != 0) { // failed to open the file
        printf("\t错误：无法打开library.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    fseek(libfp, 0, SEEK_SET), fseek(tempfp, 0, SEEK_SET);
    int n = countBook();
    for (int i = 0; i < n; ++i) {
        fread(&book, sizeof(Book), 1, libfp);
        if (i == destination) {
            --bookFound.num;
            stu.owe[stu.oweNum++] = bookFound; // 修改内存中的学生，在owe数组中添加该book
            fwrite(&bookFound, sizeof(Book), 1, tempfp);
        }
        else {
            fwrite(&book, sizeof(Book), 1, tempfp);
        }
    }
    remove(".\\library.dat");
    if (rename(".\\.library_tmp.dat", ".\\library.dat") != 0) {
        printf("\t错误：无法修改.library_tmp.dat为library.dat\n");
        printf("\t程序退出中...\n");
        exit(0);
    }
    fclose(libfp), fclose(tempfp);
    // 构建记录rec，添加进stu的借还表中
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
    // 修改内存stu完成，进入修改student.dat阶段
    if ((err = fopen_s(&stufp, ".\\student.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开student.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    if ((err = fopen_s(&tempfp, ".\\.student_temp.dat", "w+")) != 0) { // failed to open the file
        printf("\t错误：无法打开.student_temp.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    fseek(stufp, 0, SEEK_SET), fseek(tempfp, 0, SEEK_SET);
    n = countStu();
    Stu stutemp;
    for (int i = 0; i < n; ++i) {
        fread(&stutemp, sizeof(Stu), 1, stufp);
        if (i == stuIndex)
            fwrite(&stu, sizeof(Stu), 1, tempfp);
        //因为写入library时已经修改过了借还表，所以现在直接写入
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

void returnBook(char* num) {
    // 该函数会输出以num为学号未归还的书籍，让学生选择选项归还
    errno err; // 用来记录文件打开错误信息
    FILE* stufp;
    Stu stu;
    int stuIndex = searchStu(num);
    if (stuIndex == -1) {
        printf("\t错误：未找到该学生\n");
        printf("\t程序返回中...\n");
        return;
    }
    if ((err = fopen_s(&stufp, ".\\student.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开student.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    fseek(stufp, stuIndex * sizeof(Stu), SEEK_SET);
    fread(&stu, sizeof(Stu), 1, stufp);
    fclose(stufp);
    if (stu.oweNum == 0) {
        // 该学生不可以借书
        printf("\t错误：你的借阅列表为空，如需继续请先借书\n");
        printf("\t程序返回中...\n");
        return;
    }
    // 该学生可以还书，进入修改学生未还书目阶段
    printf("\t如下书目尚未归还\n");
    for (int i = 0; i < stu.oweNum; i++) {
        printf("\t %d | 《%s》\n", i, stu.owe[i].name);
    }
    printf("\t请输入归还的书目序号\n");
    int destination;
    scanf("%d", &destination);
    // 检验destination是否合法
    if (destination < 0 || destination >= stu.oweNum) {
        printf("\t错误：输入的归还书目序号不合法\n");
        printf("\t程序退出中...\n");
        return;
    }
    for (int i = destination; i < stu.oweNum - 1; i++) {
        stu.owe[i] = stu.owe[i + 1];
    }
    stu.oweNum--;
    // 修改library.dat, 将此书籍数+1
    FILE* libfp, * tempfp;
    if ((err = fopen_s(&libfp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开library.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    if ((err = fopen_s(&tempfp, ".\\.library_temp.dat", "w+")) != 0) { // failed to open the file
        printf("\t错误：无法打开library.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    fseek(libfp, 0, SEEK_SET), fseek(tempfp, 0, SEEK_SET);
    int n = countBook();
    Book book, bookFound; //book用于遍历library.dat，bookFound用于记录到借阅记录中
    for (int i = 0; i < n; ++i) {
        fread(&book, sizeof(Book), 1, libfp);
        if (i == destination) {
            ++book.num;
            bookFound = book;
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
    if ((err = fopen_s(&stufp, ".\\student.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开student.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    if ((err = fopen_s(&tempfp, ".\\.student_temp.dat", "w+")) != 0) { // failed to open the file
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
        printf("\t成功归还书本：%s\n", bookFound.name);
    }
    else {
        printf("\t错误：无法修改.library_tmp.dat为library.dat\n");
        printf("\t程序退出中...\n");
        exit(0);
    }
}