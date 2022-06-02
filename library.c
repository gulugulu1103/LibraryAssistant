#include <stdlib.h>
#include <stdio.h>
#include "class.h"
void addBook()
{
	FILE * temp;
	char Flag;
	Book book[1000];
	Book ibook[1000]; 
    errno_t err; // ×¨ÃÅÓÃÀ´¼ÇÂ¼´íÎóµÄ±äÁ¿£¬±¾ÖÊÊÇÒ»¸öint
    if ((err = fopen_s(&temp,".\\.library_temp.dat", "w+")) != 0) { // failed to open the file
        printf("\t´íÎó£ºÎŞ·¨´ò¿ª.library_temp.dat£¬´íÎó´úÂë%d\n", err);
        printf("\t³ÌĞòÍË³öÖĞ...\n");
        exit(0);
    }
    printf("\tÏÖÓĞÈçÏÂÊéÄ¿\n");
    listBook();
    printf("ÇëÑ¡ÔñÊÇ·ñÌí¼ÓÊé±¾ĞÅÏ¢(y/n):");
    Flag = getchar();
    if (Flag == 'n')
	{
		return 0;
		fclose(temp);
	}
	int i = 0,flag;
	int n = countBook();
	//Ñ­»·¼ÓÈëÊéÄ¿ 
	while (Flag == 'y')
	{ 
		//Í¼Êé±àºÅ²»ÄÜÖØ¸´
		printf("ÇëÊäÈëÍ¼Êé±àºÅ:  ");
		do
		{
			Flag = 0;
			scanf("%d", &ibook[n-1].num);
			for (i = 0; i < n; i++)
			{
				if (book[i].num == ibook[n-1].num)
				{
					flag = 1;
					printf("¸ÃÍ¼Êé±àºÅÒÑ¾­´æÔÚ,ÇëÖØĞÂÊäÈë:   ");
					break;
				}
			}
		} while (flag == 1);
	
		printf("ÇëÊäÈëÍ¼ÊéÃû³Æ:");
		scanf("%s", ibook[n-1].name);
		printf("ÇëÊäÈëÍ¼ÊéÀàĞÍ:");
		scanf("%s", ibook[n-1].type);
		
		//½«ĞÂÊéÄ¿Ğ´Èë
		if (fwrite(&ibook[n-1], sizeof(Book), 1, temp) != 1)
		{
			printf("ÎŞ·¨±£´æ¸ÃĞÅÏ¢!\n");
			return 0;
		}
		else
		{
			printf("%dºÅÍ¼ÊéĞÅÏ¢ÒÑ¾­±£´æ!\n", ibook[n-1].num);
			n++;
		}
		printf("¼ÌĞøÊäÈëĞÅÏ¢Âğ?(y/n)");
		Flag = getchar();
	}
	fclose(temp);
	printf("Ìí¼ÓÍ¼ÊéĞÅÏ¢Ö´ĞĞÍê±Ï!\n");
}
void listBook()
{
	FILE *fp;
	errno_t err;
    if ((err = fopen_s(&fp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t´íÎó£ºÎŞ·¨´ò¿ªlibrary.dat£¬´íÎó´úÂë%d\n", err);
        printf("\t³ÌĞòÍË³öÖĞ...\n");
        exit(0);
    }
    int i, record;
    Book book[i];
    record = countBook();
    if (record <= 0)
    {
    	printf ("µ±Ç°Í¼Êé¿âÀïÈ±ÉÙÊé¼®£¬ÇëÏÈÌí¼ÓÊéÄ¿")£» 
	}
	else
	{ 
		
		printf("|**********************************************************************|\n");
		printf("\n\n");
		printf("\t%-6s%-16s%-10s\n", "±àºÅ", "ÊéÃû", "ÀàĞÍ");
    	for (i = 0;i < record;i++)
    	{
    		printf("%-6d%-16s%-10s\n",book[i].num,book[i].name,book[i].type);
		}
		printf("\n\n");
		printf("|**********************************************************************|\n");
		printf("\n\n");

	}	
	return 0; 
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
