#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "library.h"
#include "student.h"
#include "menu.h"

int numCheck(char* str) {
    int n = strlen(str), cnt = 0;
    if (n != 10) return 0;
    for (int i = 0; i < n; i++) {
        if (str[i] >= '0' && str[i] <= '9') ++cnt;
    }
    return n == cnt;
}
// �ú������ڼ���str�Ƿ���10λȫ�����ַ�����������ַ�����
/*
����1���ж�������Ƿ�ȫ�������֣�����������֣���ʾѭ�����룻
����2���������������ʱ����ֹͣѭ����
*/

void adminMenu() {

    printf("\t�������Ա�����Լ���\n\t");
    char password[128], num[128];
    scanf("%s", &password);
    if (strcmp(password, "1234") != 0) {
        printf("\t���������������󣬷�����...\n");
        return;
    }
    // ����У��ɹ����������Աģʽ
    while (1) {
        int choice;

        printf("----------------------------------------------------------------");
        printf("\t       ����Աģʽ\n");
        printf("\t 1.¼��ͼ����Ϣ    \t2.�޸�ͼ����Ϣ\n");
        printf("\t 3.ɾ��ͼ����Ϣ    \t4.�鵥��ѧ���Ľ��ļ�¼\n") ;
        printf("\t 5.�鿴����ͼ����Ϣ\t 6.¼��ѧ����Ϣ\n") ;
        printf("\t 0.������ҳ\n");
        printf("\t����������ѡ��\n\t");
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            return;
        case 1:
            addBook();
            break;
        case 2:
            editBook();
            break;
        case 3:
            delBook();
            break;
        case 4:
            printf("\t������ѧ��\n\t");
            scanf("%s", num);
            if (!numCheck(num)) {
                printf("\tѧ�Ų��Ϸ���������10λ������\n");
                break;
            }
            showStu(num);
            break;
        case 5:
            listBook();
            break;
        case 6:
            printf("\t��¼��ѧ��\n\t");
            scanf("%s", num);
            printf("%s", num);
            if (!numCheck(num)) {
                printf("\tѧ�Ų��Ϸ���������10λ������\n");
                break;
            }
            addStu(num);
            break;
        default:
            printf("\t�������ޱ��Ϊ%d�Ĳ˵���������\n", choice);
        }
    }
}
// �ú�����ӡһ������Ա�˵�������Աģʽ�˵���
/*
����1����ʾ���ֲ˵�ѡ�
����2����Ҫ�û���֤����Ա���룬�����Ԥ�������1234��ͨ���������򷵻�-1��
����3����֤�������֮��Ŵ�ӡ�˵����˵��а������鼮��Ϣ����ɾ���ѡ�
*/


void stuMenu() {

    printf("\t����ѧ���Լ���\n\t");
    char num[128];
    scanf("%s", &num);
    if (searchStu(num) == -1) {
        printf("\t�����δ�ҵ���ѧ��������ϵ����Ա\n");
        return;
    }
    // ����У��ɹ����������Աģʽ
    while (1) {

        int choice;
        printf("----------------------------------------------------------------");
        printf("\t       ѧ��ģʽ\n");
        printf("\t 1.�����鼮 \t\t2.�黹�鼮\n");
        printf("\t 3.��ѯ����ļ�¼\n") ;
        printf("\t 0.������ҳ\n");
        printf("\t����������ѡ��\n\t");
        scanf("%d", &choice);
        switch (choice) {
        case 0:
            return;
        case 1:
            borrowBook(num);
            break;
        case 2:
            returnBook(num);
            break;
        case 3:
            showStu(num);
            break;
        default:
            printf("\t�������ޱ��Ϊ%d�Ĳ˵���������\n", choice);
        }
    }
}
// �ú�����ӡһ��ѧ���˵��������û������ѡ�
/*
����1����ʾ���ֲ˵�ѡ��
����2����Ҫ�û�����ѧ�ţ�����numCheck()��������ѧ���Ƿ�Ϸ���������Ϸ��򷵻�-1;
����3��ѧ�źϷ�֮��Ŵ�ӡ�˵����˵��а�����ѧ���Խ軹��Ĳ�ѯ�����ӣ����軹�����ܡ�(Ū�����ˣ�
*/

//�˵����û��Ѻ�Ϊ��ּ����ʾ��Ϣ����Ҫ�У������û��Ѻ�
void mainMenu() {

    int choice;
    printf("----------------------------------------------------------------");
    printf("\t\t���������ʵ��\t��ĩ����ҵ\n");
    printf("\t\t��ӭ����ͼ�����ϵͳ\t\t\t�������в���%d��\n", countBook());
    printf("\t1.��ѧ����ݼ���\n");
    printf("\t2.�Թ���Ա��ݼ���\n");
    printf("\t0.�˳�ϵͳ\n");
    printf("\n\t����������ѡ��\n");
    printf("\t");
    scanf("%d", &choice);
    switch (choice) {
    case 0:
        printf("\t��л���Ĺ���\n");
        system("PAUSE");
        exit(0);
    case 1:
        stuMenu();
        break;
    case 2:
        adminMenu();
        break;
    default:
        printf("\t�������ޱ��Ϊ%d�Ĳ˵���������\n", choice);
    }
}
// �ú�����ӡһ�����˵�
/*
���˵������ǳ��������ڣ���һ����˵������˹���Ա��ں�ѧ����ڡ�
����1����ʾ���ֲ˵�ѡ�
����2�����˵����Ͻǿ���ʾ�ݲ��鼮��������
*/
