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
    // 该函数返回学生总数
    errno = 0; // 用来记录文件打开错误信息
    FILE* fp = fopen("student.dat", "rb+");
    if (!fp) {
        if (errno == 2) {
            return 0;
        }
        printf("\t错误：无法打开student.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
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

int searchStu(char* num) {
    // 在"student.dat"中查找以num为学号的学生，返回学生的顺位, 若没有找到则返回-1。
    if (countStu() == 0) {
        return -1;
    }
    int index = -1;
    errno = 0; // 用来记录文件打开错误信息
    FILE* fp = fopen("student.dat", "rb+");
    if (!fp) {
        if (errno == 2) {
            printf("\t没有student.dat文件，请先创建学生\n\t");
            errno = 0; // 错误恢复标志
            system("PAUSE");
            return -1;
        }
        printf("\t错误：无法打开student.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
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
    fclose(fp);
    return index;
}

void addStu(char* num) {
    // 在"student.dat"中以追加模式新建以num为学号的学生
    if (searchStu(num) > -1) {
        printf("\t错误：该学生已存在\n\t");
        system("PAUSE");
        return;
    }
    errno = 0; // 用来记录文件打开错误信息
    FILE* fp = fopen("student.dat", "ab+");
    if (!fp) {
        if (errno != 2) {
            printf("\t错误：无法打开student.dat，错误代码%d：%s\n\t", errno, strerror(errno));
            system("PAUSE");
            exit(0);
        }
    }
    Stu stu; // 初始化一个学生
    stu.oweNum = stu.recNum = 0;
    Book book;
    Rec rec;
    for (int i = 0; i < 21; i++) {
        stu.owe[i] = book;
        stu.rec[i] = rec;
    }
    strcpy(stu.num, num);
    fwrite(&stu, sizeof(Stu), 1, fp);
    printf("\t成功添加学号为%s学生\n\t", stu.num);
    system("PAUSE");
    fclose(fp);
}

void showStu(char* num) {
    // 调用searchStu()函数, 输出以num为学号的学生的近15条借阅记录
    errno = 0; // 用来记录文件打开错误信息
    FILE* fp = fopen("student.dat", "rb+");
    if (!fp) {
        if (errno == 2) {
            printf("\t没有student.dat文件，请先创建学生\n\t");
            errno = 0; // 错误恢复标志
            system("PAUSE");
            return;
        }
        printf("\t错误：无法打开student.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    Stu stu;
    int stuIndex = searchStu(num);
    if (stuIndex == -1) {
        printf("\t错误：找不到学号为%s的学生\n\t", num);
        printf("\t程序退出中...\n");
        fclose(fp);
        system("PAUSE");
        return;
    }
    fseek(fp, stuIndex * sizeof(Stu), SEEK_SET);
    fread(&stu, sizeof(Stu), 1, fp);
    if (!stu.recNum) {
        printf("\t你暂没有借阅记录\n\t");
        system("PAUSE");
        fclose(fp);
        return;
    }
    Rec rec; // 记录
    for (int i = 0; i < stu.recNum; i++) {
        rec = stu.rec[i];
        printf("\t %d | 《%s》 | %s | %s\n", i, \
            rec.book.name, rec.time, (rec.borrow ? "借 出 " : "归还"));
    }
    fclose(fp);
}

void borrowBook(char* num) {
    // 该函数调用library库中的listBook()函数，询问用户借阅书目的序号,修改library.dat与student.dat
    // 先检验学生是否能借书
    errno = 0; // 用来记录文件打开错误信息
    int n = countBook();
    if (n == 0) {
        printf("\t错误：没有书目信息，请联系管理员添加数目信息\n\t");
        system("PAUSE");
        return;
    }
    FILE* libfp, * tempfp, * stufp;
    Stu stu;
    int stuIndex = searchStu(num);
    if (stuIndex == -1) {
        printf("\t错误：未找到该学生\n");
        printf("\t程序返回中...\n\t");
        system("PAUSE");
        return;
    }
    stufp = fopen("student.dat", "rb+");
    if (!stufp) {
        if (errno == 2) {
            printf("\t没有student.dat文件，请先创建学生\n\t");
            errno = 0; // 错误恢复标志
            system("PAUSE");
            return;
        }
        printf("\t错误：无法打开student.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    fseek(stufp, stuIndex * sizeof(Stu), SEEK_SET);
    fread(&stu, sizeof(Stu), 1, stufp);
    fclose(stufp);
    if (stu.oweNum >= 5) {
        // 该学生不可以借书
        printf("\t错误：你的借书数量已经达到最大上限，如需继续请先还书\n");
        printf("\t程序返回中...\n\t");
        system("PAUSE");
        return;
    }
    // 该学生可以借书，列出书籍，询问想借阅的书籍
    printf("\t现有如下书目\n");
    listBook();
    printf("\t请输入借阅的书目序号\n\t");
    int destination;
    scanf("%d", &destination);
    if (destination < 0 || destination >= countBook()) {
        printf("\t错误：输入了错误的书目序号\n");
        printf("\t程序返回中...\n\t");
        system("PAUSE");
        return;
    }
    // 检测该书籍是否还有库存(即book.num > 0)
    libfp = fopen("library.dat", "rb+");
    if (!libfp) {
        if (errno == 2) {
            printf("\t没有library.dat文件，请先录入书籍\n\t");
            errno = 0; // 错误恢复标志
            system("PAUSE");
            return;
        }
        printf("\t错误：无法打开library.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    fseek(libfp, destination * sizeof(Book), SEEK_SET);
    Book book, bookFound; //book用于遍历library.dat，bookFound用于记录到借阅记录中
    fread(&bookFound, sizeof(Book), 1, libfp);
    fclose(libfp);
    if (bookFound.num <= 0) { // bookFound.num 不可以-1
        printf("\t错误：该书目不可借阅，因为其数量为0\n");
        printf("\t程序返回中...\n\t");
        system("PAUSE");
        return;
    }
    // 已经选择目标书目，进入修改library.dat阶段，让所选书目数量-1
    libfp = fopen("library.dat", "rb+");
    if (!libfp) {
        if (errno == 2) {
            printf("\t没有library.dat文件，请先创建学生\n\t");
            errno = 0; // 错误恢复标志
            system("PAUSE");
            return;
        }
        printf("\t错误：无法打开library.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    tempfp = fopen(".library_temp.dat", "wb+");
    if (!tempfp) {
        printf("\t错误：无法打开.library_temp.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    fseek(libfp, 0, SEEK_SET), fseek(tempfp, 0, SEEK_SET);
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
    fclose(libfp), fclose(tempfp), fclose(stufp);
    if (remove("library.dat") != 0) {
        printf("\t错误：无法删除library.dat\n");
        printf("\terrno = %d\n: %s", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    if (rename(".library_temp.dat", "library.dat") != 0) {
        printf("\terrno = %d\n: %s", errno, strerror(errno));
        printf("\t错误：无法修改.library_temp.dat为library.dat\n");
        printf("\t程序退出中...\n\t");
        system("PAUSE");
        exit(0);
    }
    // 构建记录rec，添加进stu的借还表中
    time_t rawtime;
    time(&rawtime);
    // Rec rec = { bookFound, ctime(&rawtime), 1 };
    Rec rec;
    rec.book = bookFound;
    rec.borrow = 1;
    strcpy(rec.time, ctime(&rawtime));
    stu.rec[stu.recNum++] = rec;
    while (stu.recNum >= 16) {
        // 让stu.recNum始终保持15条
        for (int i = 0; i < stu.recNum; ++i) {
            stu.rec[i] = stu.rec[i + 1];
        }
        --stu.recNum;
    }
    // 修改内存stu完成，进入修改student.dat阶段
    stufp = fopen("student.dat", "rb+");
    if (!stufp) {
        if (errno == 2) {
            printf("\t没有student.dat文件，请先创建学生\n\t");
            errno = 0; // 错误恢复标志
            system("PAUSE");
            return;
        }
        printf("\t错误：无法打开student.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    tempfp = fopen(".student_temp.dat", "wb+");
    if (!tempfp) {
        printf("\t错误：无法打开.student_temp.dat，错误代码%d：%s\n\t", errno, strerror(errno));
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
        //因为写入library时已经修改过了借还表，所以现在直接写入
        else
            fwrite(&stutemp, sizeof(Stu), 1, tempfp);
    }
    if (fclose(tempfp) != 0) {
        printf("\t无法关闭tempfp\n");
        printf("\terrno = %d\n: %s", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    if (fclose(stufp) != 0) {
        printf("\t无法关闭stufp\n");
        printf("\terrno = %d\n: %s", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    if (remove("student.dat") != 0) {
        printf("\t错误：无法删除student.dat\n");
        printf("\terrno = %d\n: %s", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    if (rename(".student_temp.dat", "student.dat") == 0) {
        // 重命名成功
        printf("\t成功借阅书本：%s\n\t", bookFound.name);
        system("PAUSE");
    }
    else {
        printf("\terrno = %d\n: %s", errno, strerror(errno));
        printf("\t错误：无法修改.library_temp.dat为library.dat\n");
        printf("\t程序退出中...\n\t");
        system("PAUSE");
        exit(0);
    }
}

void returnBook(char* num) {
    // 该函数会输出以num为学号未归还的书籍，让学生选择选项归还
    errno = 0; // 用来记录文件打开错误信息
    FILE* stufp, * tempfp, * libfp;
    Stu stu;
    int stuIndex = searchStu(num);
    if (stuIndex == -1) {
        printf("\t错误：未找到该学生\n");
        printf("\t程序返回中...\n\t");
        system("PAUSE");
        return;
    }
    stufp = fopen("student.dat", "rb+");
    if (!stufp) {
        if (errno == 2) {
            printf("\t没有student.dat文件，请先创建学生\n\t");
            errno = 0; // 错误恢复标志
            system("PAUSE");
            return;
        }
        printf("\t错误：无法打开student.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    fseek(stufp, stuIndex * sizeof(Stu), SEEK_SET);
    fread(&stu, sizeof(Stu), 1, stufp);
    fclose(stufp);
    if (stu.oweNum == 0) {
        // 该学生不可以借书
        printf("\t错误：你的借阅列表为空，如需继续请先借书\n");
        printf("\t程序返回中...\n\t");
        system("PAUSE");
        return;
    }
    // 该学生可以还书，进入修改学生未还书目阶段
    printf("\t如下书目尚未归还\n");
    for (int i = 0; i < stu.oweNum; i++) {
        printf("\t %d  | 《%s》\n", i, stu.owe[i].name);
    }
    printf("\t请输入归还的书目序号\n\t");
    Book book, bookReturned; //book用于遍历library.dat，bookFound用于记录到借阅记录中
    int destination;
    scanf("%d", &destination);
    // 检验destination是否合法
    if (destination < 0 || destination >= stu.oweNum) {
        printf("\t错误：输入的归还书目序号不合法\n");
        printf("\t程序退出中...\n\t");
        system("PAUSE");
        return;
    }
    bookReturned = stu.owe[destination];
    for (int i = destination; i < stu.oweNum - 1; i++) {
        stu.owe[i] = stu.owe[i + 1];
    }
    stu.oweNum--;
    // 修改library.dat, 将此书籍数+1
    libfp = fopen("library.dat", "rb+");
    if (!libfp) {
        if (errno == 2) {
            printf("\t没有library.dat文件，请先创建学生\n\t");
            errno = 0; // 错误恢复标志
            system("PAUSE");
            return;
        }
        printf("\t错误：无法打开library.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    tempfp = fopen(".library_temp.dat", "wb+");
    if (!tempfp) {
        printf("\t错误：无法打开.library_temp.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    fseek(libfp, 0, SEEK_SET), fseek(tempfp, 0, SEEK_SET);
    int n = countBook();
    for (int i = 0; i < n; ++i) {
        fread(&book, sizeof(Book), 1, libfp);
        if (strcmp(bookReturned.name, book.name) == 0) {
            ++book.num;
        }
        fwrite(&book, sizeof(Book), 1, tempfp);
    }
    fclose(libfp), fclose(tempfp), fclose(stufp);
    if (remove("library.dat") != 0) {
        printf("\t错误：无法删除library.dat\n");
        printf("\terrno = %d\n: %s", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    if (rename(".library_temp.dat", "library.dat") != 0) {
        printf("\terrno = %d\n: %s", errno, strerror(errno));
        printf("\t错误：无法修改.library_temp.dat为library.dat\n");
        printf("\t程序退出中...\n\t");
        system("PAUSE");
        exit(0);
    }
    // 构建记录，添加进stu
    time_t rawtime;
    time(&rawtime);
    // Rec rec = { bookFound, ctime(&rawtime), 1 };
    Rec rec;
    rec.book = bookReturned;
    rec.borrow = 0;
    strcpy(rec.time, ctime(&rawtime));
    stu.rec[stu.recNum++] = rec;
    while (stu.recNum >= 16) {
        // 让stu.recNum始终保持15条
        for (int i = 0; i < stu.recNum; ++i) {
            stu.rec[i] = stu.rec[i + 1];
        }
        --stu.recNum;
    }
    // 修改完成，进入修改student.dat阶段
    stufp = fopen("student.dat", "rb+");
    if (!stufp) {
        if (errno == 2) {
            printf("\t没有student.dat文件，请先创建学生\n\t");
            errno = 0; // 错误恢复标志
            system("PAUSE");
            return;
        }
        printf("\terrno = %d\n: %s", errno, strerror(errno));
        printf("\t错误：无法打开student.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    tempfp = fopen(".student_temp.dat", "wb+");
    if (!tempfp) {
        printf("\terrno = %d\n: %s", errno, strerror(errno));
        printf("\t错误：无法打开.student_temp.dat，错误代码%d：%s\n\t", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
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
    fclose(tempfp), fclose(libfp), fclose(stufp);
    if (remove("student.dat") != 0) {
        printf("\t错误：无法删除student.dat\n");
        printf("\terrno = %d\n: %s", errno, strerror(errno));
        system("PAUSE");
        exit(0);
    }
    // printf("\terrno = %d\n: %s", errno, strerror(errno));
    if (rename(".student_temp.dat", "student.dat") == 0) {
        // 重命名成功
        printf("\t成功归还书本：%s\n\t", bookReturned.name);
        system("PAUSE");
    }
    else {
        printf("\terrno = %d\n: %s", errno, strerror(errno));
        printf("\t错误：无法修改.library_temp.dat为library.dat\n");
        printf("\t程序退出中...\n");
        system("PAUSE");
        exit(0);
    }
}
