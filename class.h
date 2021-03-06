#ifndef __CLASS_H
#define __CLASS_H


// 这里放着所有对象

typedef struct {
    // 一本书
    char name[81];
    char type[81];
    int num; // 书的数量
} Book;

typedef struct {
    // 一条记录
    Book book; // 记录的对象，书本
    char time[81]; // 时间字符串
    int borrow;  // borrow = 1 是借出, borrow = 0 是归还
} Rec;

typedef struct {
    // 学生
    char num[15];
    Rec rec[21]; // 借还记录数组
    int recNum; // 借还记录数量
    Book owe[21]; // 未还的书本
    int oweNum; // 未还的书本数量
} Stu;

#endif