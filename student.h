#ifndef __STUDENT_H
#define __STUDENT_H

int countStu();
// �ú�������ѧ������

int searchStu(char* num);
// ��"student.dat"�в�����numΪѧ�ŵ�ѧ��������ѧ����˳λ, ��û���ҵ��򷵻�-1��

void addStu(char* num);
// ��"student.dat"����׷��ģʽ�½���numΪѧ�ŵ�ѧ��

void showStu(char* num);
// ����searchStu()����, �����numΪѧ�ŵ�ѧ���Ľ�15�����ļ�¼

void borrowBook(char* num);
// �ú�������library���е�listBook()������ѯ���û�������Ŀ�����,�޸�library.dat��student.dat

void returnBook(char* num);
// �ú����������numΪѧ��δ�黹���鼮����ѧ��ѡ��ѡ��黹

#endif