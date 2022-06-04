#include <stdlib.h>
#include <stdio.h>
#include "class.h"
void addBook()
{
	FILE * temp;
	Book ibook;//用以添加额外书籍的变量ibook 
	Book book;// 初始化一个book; 
    errno_t err; // 专门用来记录错误的变量，本质是一个int
    if ((err = fopen_s(&temp,".\\.library_temp.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开.library_temp.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    printf("\t现有如下书目\n");
    listBook();
	int i = 0,flag;
	int n = countBook();
	//循环加入书目 
	//输入需要添加的书本信息 
	printf("\t请按顺序输入书名,书籍类型,书目数量：（中间空格隔开）\n");
	do
	{
		flag = 1;
		scanf("%s %s %d", &ibook.name, &ibook.type, %ibook.num);
		for (i = 0;i < n;i++)
		{
			fread(&book,sizeof(Book),1,temp);
			if (strcmp(ibook.name,book.name) == 0)
			{
				printf("\t该图书已经存在,请重新输入:   ");
				break;
			}
			else
			{
				flag = 0;
			} 
		}
	} while (flag == 1);
	//将新书目写入
	if (fwrite(&ibook, sizeof(Book), 1, temp) != 1)
	{
		printf("\t无法保存该信息!\n");
		return 0;
	}
	else
	{
		printf("\t新图书信息已经保存!\n");
		n++;
	}
	fclose(temp);
	printf("\t添加该图书信息执行完毕!\n");
}
void listBook()
{
	FILE *fp;
	errno_t err;
    if ((err = fopen_s(&fp, ".\\library.dat", "r+")) != 0) 
	{ 
		// failed to open the file
        printf("\t错误：无法打开library.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    int i,number = 0,n;
    n = countBook();
    char ch;//判断文件是否为空 
    Book book;
    ch = fgets(fp);
    if(ch == EOF)
	{
		printf("暂时无书目记录，请先添加书目！"); 
	} 
	else
	{
		printf("\t|**********************************************************************|\n");
		printf("\n\n");
		printf("\t%-16s%-10s%-6d\n", "书名", "类型","数量");
	   	for (int i = 0; i < n; i++) 
		{
        	fread(&book, sizeof(Book), 1, fp);
	   		printf("\t%d%-16s%-10s%-6d\n",number,book.name,book.type,book.num);
	   		number++;
		}
		printf("\n\n");
		printf("\t|**********************************************************************|\n");
		printf("\n\n");
	}
	fclose(fp); 
	return 0; 
}
int  countBook()
{
	int record = 0;
	Book book;
	FILE *fp;
	errno_t err;
    if ((err = fopen_s(&fp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开library.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
	while(!feof(fp))
	{
		fread(&book,sizeof(Book),1,fp);
		record++;
	}
	fclose(fp);
	return record; 
}
void delBook() {
    // 璇ュ嚱鏁拌皟鐢╨istBook()锛岄殢鍚庢帴鏀剁敤鎴风殑搴忓彿鏉ュ垹闄や功鐩�
    FILE* fp, * temp;
    errno_t err; // 涓撻棬鐢ㄦ潵璁板綍閿欒鐨勫彉閲忥紝鏈川鏄竴涓猧nt
    if ((err = fopen(&fp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t閿欒锛氭棤娉曟墦寮�library.dat锛岄敊璇唬鐮�%d\n", err);
        printf("\t绋嬪簭閫�鍑轰腑...\n");
        exit(0);
    }
    if ((err = fopen(&temp, ".\\.library_temp.dat", "w+")) != 0) { // failed to open the file
        printf("\t閿欒锛氭棤娉曟墦寮�.library_temp.dat锛岄敊璇唬鐮�%d\n", err);
        printf("\t绋嬪簭閫�鍑轰腑...\n");
        exit(0);
    }
    printf("\t鐜版湁濡備笅涔︾洰\n");
    listBook();
    printf("\t璇疯緭鍏ラ渶瑕佸垹闄ょ殑涔︾洰搴忓彿浠ョ户缁璡n");
    int input, n = countBook();
    scanf("%d", &input);
    if (!(input >= 0 && input < n)) {
        printf("\t閿欒锛氳緭鍏ョ殑涔︾洰搴忓彿涓嶅悎娉昞n");
        printf("\t杩斿洖涓�...\n");
        fclose(fp), fclose(temp);
        return;
    }
    fseek(fp, 0, SEEK_SET), fseek(temp, 0, SEEK_SET);
    Book book;
    for (int i = 0; i < n; i++) {
        fread(&book, sizeof(Book), 1, fp);
        if (i == input) continue;
        else fwrite(&book, sizeof(Book), 1, temp);
    }
    remove(".\\library.dat");
    if (rename(".\\.library_tmp.dat", ".\\library.dat") == 0) {
        // 閲嶅懡鍚嶆垚鍔�
        printf("\t鍒犻櫎鎴愬姛\n");
    }
    else {
        printf("\t閿欒锛氭棤娉曚慨鏀筶ibrary_tmp.dat涓簂ibrary.dat\n");
        printf("\t绋嬪簭閫�鍑轰腑...\n");
        fclose(fp), fclose(temp);
        exit(0);
    }
}

void editBook() {
    // 璇ュ嚱鏁拌皟鐢╨istBook(), 闅忓悗鎺ユ敹鐢ㄦ埛鐨勫簭鍙锋潵淇敼涔︾洰
    FILE* fp, * temp;
    errno_t err; // 鐢ㄦ潵璁板綍
    if ((err = fopen(&fp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t閿欒锛氭棤娉曟墦寮�library.dat锛岄敊璇唬鐮�%d\n", err);
        printf("\t绋嬪簭閫�鍑轰腑...\n");
        exit(0);
    }
    if ((err = fopen(&temp, ".\\.library_temp.dat", "w+")) != 0) { // failed to open the file
        printf("\t閿欒锛氭棤娉曟墦寮�.library_temp.dat锛岄敊璇唬鐮�%d\n", err);
        printf("\t绋嬪簭閫�鍑轰腑...\n");
        exit(0);
    }
    printf("\t鐜版湁濡備笅涔︾洰\n");
    listBook();
    printf("\t璇疯緭鍏ラ渶瑕佷慨鏀圭殑涔︾洰搴忓彿浠ョ户缁璡n");
    int input, n = countBook();
    scanf("%d", &input);
    if (!(input >= 0 && input < n)) {
        printf("\t閿欒锛氳緭鍏ョ殑涔︾洰搴忓彿涓嶅悎娉昞n");
        printf("杩斿洖涓�...");
        fclose(fp), fclose(temp);
        return;
    }
    Book edited;
    printf("\t璇疯緭鍏ヤ功鐩悕绉帮細\n");
    scanf("%s", edited.name);
    printf("\t璇疯緭鍏ヤ功鐩被鍨嬶細\n");
    scanf("%s", edited.type);
    fseek(fp, 0, SEEK_SET), fseek(temp, 0, SEEK_SET);
    Book book;
    for (int i = 0; i < n; i++) {
        fread(&book, sizeof(Book), 1, fp);
        if (i == input) fwrite(&edited, sizeof(Book), 1, temp);
        else fwrite(&book, sizeof(Book), 1, temp);
    }
    remove(".\\library.dat");
    if (rename(".\\.library_tmp.dat", ".\\library.dat") == 0) {
        // 閲嶅懡鍚嶆垚鍔�
        printf("\t鎴愬姛淇敼涔﹀悕涓猴細%s\n", edited.name);
    }
    else {
        printf("\t閿欒锛氭棤娉曚慨鏀�.library_tmp.dat涓簂ibrary.dat\n");
        printf("\t绋嬪簭閫�鍑轰腑...\n");
        exit(0);
    }
}
