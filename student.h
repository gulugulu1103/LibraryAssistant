#ifndef __STUDENT_H
#define __STUDENT_H

int countStu();
// 该函数返回学生总数

int searchStu(char* num);
// 在"student.dat"中查找以num为学号的学生，返回学生的顺位, 若没有找到则返回-1。

void addStu(char* num);
// 在"student.dat"中以追加模式新建以num为学号的学生

void showStu(char* num);
// 调用searchStu()函数, 输出以num为学号的学生的近15条借阅记录

void borrowBook(char* num);
// 该函数调用library库中的listBook()函数，询问用户借阅书目的序号,修改library.dat与student.dat

void returnBook(char* num);
// 该函数会输出以num为学号未归还的书籍，让学生选择选项归还

#endif