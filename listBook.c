void listBook()
{
	FILE *fp;
	errno_t err;
    if ((err = fopen_s(&fp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t错误：无法打开library.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    int i, record;
    Book book[i];
    record = countBook();
    if (record <= 0)
    {
    	printf ("当前图书库里缺少书籍，请先添加书目")； 
	}
	else
	{ 
		
		printf("|**********************************************************************|\n");
		printf("\n\n");
		printf("\t%-6s%-16s%-10s\n", "编号", "书名", "类型");
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
 
