void listBook()
{
	FILE *fp;
	errno_t err;
    if ((err = fopen_s(&fp, ".\\library.dat", "r+")) != 0) { // failed to open the file
        printf("\t�����޷���library.dat���������%d\n", err);
        printf("\t�����˳���...\n");
        exit(0);
    }
    int i, record;
    Book book[i];
    record = countBook();
    if (record <= 0)
    {
    	printf ("��ǰͼ�����ȱ���鼮�����������Ŀ")�� 
	}
	else
	{ 
		
		printf("|**********************************************************************|\n");
		printf("\n\n");
		printf("\t%-6s%-16s%-10s\n", "���", "����", "����");
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
 
