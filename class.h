#ifndef __CLASS_H
#define __CLASS_H


// ����������ж���

typedef struct {
    // һ����
    char name[81];
    char type[81];
    int num; // �������
} Book;

typedef struct {
    // һ����¼
    Book book; // ��¼�Ķ����鱾
    char time[81]; // ʱ���ַ���
    int borrow;  // borrow = 1 �ǽ��, borrow = 0 �ǹ黹
} Rec;

typedef struct {
    // ѧ��
    char num[81];
    Rec rec[21]; // �軹��¼����
    int recNum; // �軹��¼����
    Book owe[21]; // δ�����鱾
    int oweNum; // δ�����鱾����
} Stu;

#endif