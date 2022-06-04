 #include <stdlib.h>
#include <stdio.h>
#include "class.h"
void addBook()
{
	FILE * temp;
	char Flag;
	Book ibook;//ÓÃÒÔÌí¼Ó¶îÍâÊé¼®µÄ±äÁ¿ibook 
	Book book;// ³õÊ¼»¯Ò»¸öbook; 
    errno_t err; // ×¨ÃÅÓÃÀ´¼ÇÂ¼´íÎóµÄ±äÁ¿£¬±¾ÖÊÊÇÒ»¸öint
    if ((err = fopen_s(&temp,".\\.library_temp.dat", "a+")) != 0) { // failed to open the file
        printf("\t´íÎó£ºÎŞ·¨´ò¿ª.library_temp.dat£¬´íÎó´úÂë%d\n", err);
        printf("\t³ÌĞòÍË³öÖĞ...\n");
        exit(0);
    }
    printf("\tÏÖÓĞÈçÏÂÊéÄ¿\n");
    listBook();
    printf("\tÇëÑ¡ÔñÊÇ·ñÌí¼ÓÊé±¾ĞÅÏ¢(y/n):");
    Flag = getchar();
    if (Flag == 'n')
	{
		fclose(temp);
		exit(0); 
	}
	int i = 0,flag;
	int n = countBook();
	//Ñ­»·¼ÓÈëÊéÄ¿ 
	while (Flag == 'y')
	{ 
		//ÊäÈëĞèÒªÌí¼ÓµÄÊé±¾ĞÅÏ¢ 
		printf("\tÇë°´Ë³ĞòÊäÈëÊéÃû£¬Êé¼®ÀàĞÍ£º£¨ÖĞ¼ä¿Õ¸ñ¸ô¿ª£©\n");
		do
		{
			flag = 1;
			scanf("%s %s", &ibook.name, &ibook.type);
			for (fread(&book, sizeof(Book), 1, temp) != EOF)
			{
				if (strcmp(ibook.name,book.name) == 0)
				{
					printf("\t¸ÃÍ¼ÊéÒÑ¾­´æÔÚ,ÇëÖØĞÂÊäÈë:   ");
					break;
				}
				else
				{
					flag = 0;
				} 
			}
		} while (flag == 1);
		//½«ĞÂÊéÄ¿Ğ´Èë
		if (fwrite(&ibook, sizeof(Book), 1, temp) != 1)
		{
			printf("\tÎŞ·¨±£´æ¸ÃĞÅÏ¢!\n");
			return 0;
		}
		else
		{
			printf("\tĞÂÍ¼ÊéĞÅÏ¢ÒÑ¾­±£´æ!\n");
			n++;
		}
		printf("\t¼ÌĞøÊäÈëĞÅÏ¢Âğ?(y/n)");
		Flag = getchar();
	}
	fclose(temp);
	printf("\tÌí¼Ó¸ÃÍ¼ÊéĞÅÏ¢Ö´ĞĞÍê±Ï!\n");
}
void listBook()
{
	FILE *fp;
	errno_t err;
    if ((err = fopen_s(&fp, ".\\library.dat", "r+")) != 0) 
	{ 
		// failed to open the file
        printf("\t´íÎó£ºÎŞ·¨´ò¿ªlibrary.dat£¬´íÎó´úÂë%d\n", err);
        printf("\t³ÌĞòÍË³öÖĞ...\n");
        exit(0);
    }
    int i,number = 0;
    Book book;
    if (record <= 0)
    {
    	printf ("\tµ±Ç°Í¼Êé¿âÀïÈ±ÉÙÊé¼®£¬ÇëÏÈÌí¼ÓÊéÄ¿");
	}
	else
	{ 
		
		printf("\t|**********************************************************************|\n");
		printf("\n\n");
		printf("\t%-16s%-10s\n", "ÊéÃû", "ÀàĞÍ");
    	for (fread(&book, sizeof(Book), 1, fp) != EOF)
    	{
    		printf("\t%d%-16s%-10s\n",number,book.name,book.type);
    		number++;
		}
		printf("\n\n");
		printf("\t|**********************************************************************|\n");
		printf("\n\n");

	}	
	return 0; 
}
int  countBook()
{
	int record = 0;
	Book book;
	FILE *fp;
	errno_t err;
    if ((err = fopen_s(&fp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t´íÎó£ºÎŞ·¨´ò¿ªlibrary.dat£¬´íÎó´úÂë%d\n", err);
        printf("\t³ÌĞòÍË³öÖĞ...\n");
        exit(0);
    }
    while (fread(&book, sizeof(Book), 1, fp) != EOF)
	{
			record++;
	}
	if (!feof(fp))
	{
		printf("\tÎ´ÄÜ¹»¶Áµ½ÎÄÄ©"); 
	}
	fclose(fp);
	return record; 
}
void delBook() {
    // è¯¥å‡½æ•°è°ƒç”¨listBook()ï¼Œéšåæ¥æ”¶ç”¨æˆ·çš„åºå·æ¥åˆ é™¤ä¹¦ç›®
    FILE* fp, * temp;
    errno_t err; // ä¸“é—¨ç”¨æ¥è®°å½•é”™è¯¯çš„å˜é‡ï¼Œæœ¬è´¨æ˜¯ä¸€ä¸ªint
    if ((err = fopen(&fp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\té”™è¯¯ï¼šæ— æ³•æ‰“å¼€library.datï¼Œé”™è¯¯ä»£ç %d\n", err);
        printf("\tç¨‹åºé€€å‡ºä¸­...\n");
        exit(0);
    }
    if ((err = fopen(&temp, ".\\.library_temp.dat", "w+")) != 0) { // failed to open the file
        printf("\té”™è¯¯ï¼šæ— æ³•æ‰“å¼€.library_temp.datï¼Œé”™è¯¯ä»£ç %d\n", err);
        printf("\tç¨‹åºé€€å‡ºä¸­...\n");
        exit(0);
    }
    printf("\tç°æœ‰å¦‚ä¸‹ä¹¦ç›®\n");
    listBook();
    printf("\tè¯·è¾“å…¥éœ€è¦åˆ é™¤çš„ä¹¦ç›®åºå·ä»¥ç»§ç»­\n");
    int input, n = countBook();
    scanf("%d", &input);
    if (!(input >= 0 && input < n)) {
        printf("\té”™è¯¯ï¼šè¾“å…¥çš„ä¹¦ç›®åºå·ä¸åˆæ³•\n");
        printf("\tè¿”å›ä¸­...\n");
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
        // é‡å‘½åæˆåŠŸ
        printf("\tåˆ é™¤æˆåŠŸ\n");
    }
    else {
        printf("\té”™è¯¯ï¼šæ— æ³•ä¿®æ”¹library_tmp.datä¸ºlibrary.dat\n");
        printf("\tç¨‹åºé€€å‡ºä¸­...\n");
        fclose(fp), fclose(temp);
        exit(0);
    }
}

void editBook() {
    // è¯¥å‡½æ•°è°ƒç”¨listBook(), éšåæ¥æ”¶ç”¨æˆ·çš„åºå·æ¥ä¿®æ”¹ä¹¦ç›®
    FILE* fp, * temp;
    errno_t err; // ç”¨æ¥è®°å½•
    if ((err = fopen(&fp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\té”™è¯¯ï¼šæ— æ³•æ‰“å¼€library.datï¼Œé”™è¯¯ä»£ç %d\n", err);
        printf("\tç¨‹åºé€€å‡ºä¸­...\n");
        exit(0);
    }
    if ((err = fopen(&temp, ".\\.library_temp.dat", "w+")) != 0) { // failed to open the file
        printf("\té”™è¯¯ï¼šæ— æ³•æ‰“å¼€.library_temp.datï¼Œé”™è¯¯ä»£ç %d\n", err);
        printf("\tç¨‹åºé€€å‡ºä¸­...\n");
        exit(0);
    }
    printf("\tç°æœ‰å¦‚ä¸‹ä¹¦ç›®\n");
    listBook();
    printf("\tè¯·è¾“å…¥éœ€è¦ä¿®æ”¹çš„ä¹¦ç›®åºå·ä»¥ç»§ç»­\n");
    int input, n = countBook();
    scanf("%d", &input);
    if (!(input >= 0 && input < n)) {
        printf("\té”™è¯¯ï¼šè¾“å…¥çš„ä¹¦ç›®åºå·ä¸åˆæ³•\n");
        printf("è¿”å›ä¸­...");
        fclose(fp), fclose(temp);
        return;
    }
    Book edited;
    printf("\tè¯·è¾“å…¥ä¹¦ç›®åç§°ï¼š\n");
    scanf("%s", edited.name);
    printf("\tè¯·è¾“å…¥ä¹¦ç›®ç±»å‹ï¼š\n");
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
        // é‡å‘½åæˆåŠŸ
        printf("\tæˆåŠŸä¿®æ”¹ä¹¦åä¸ºï¼š%s\n", edited.name);
    }
    else {
        printf("\té”™è¯¯ï¼šæ— æ³•ä¿®æ”¹.library_tmp.datä¸ºlibrary.dat\n");
        printf("\tç¨‹åºé€€å‡ºä¸­...\n");
        exit(0);
    }
}
