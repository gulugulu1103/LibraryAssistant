void addBook()
{
	FILE* fp, * temp;
	char Flag;
	Book book[1000];
	Book ibook[1000]; 
    errno_t err; // ר��������¼����ı�����������һ��int
    if ((err = fopen_s(&temp,".\\.library_temp.dat", "w+")) != 0) { // failed to open the file
        printf("\t�����޷���.library_temp.dat���������%d\n", err);
        printf("\t�����˳���...\n");
        exit(0);
    }
    printf("\t����������Ŀ\n");
    listBook();
    printf("��ѡ���Ƿ�����鱾��Ϣ(y/n):");
    Flag = getchar();
    if (Flag == 'n')
	{
		return 0;
		fclose(fp),fclose(temp);
	}
	int i = 0,flag;
	int n = countBook();
	//ѭ��������Ŀ 
	while (Flag == 'y')
	{ 
		//ͼ���Ų����ظ�
		printf("������ͼ����:  ");
		do
		{
			Flag = 0;
			scanf("%d", &ibook[n-1].num);
			for (i = 0; i < n; i++)
			{
				if (book[i].num == ibook[n-1].num)
				{
					flag = 1;
					printf("��ͼ�����Ѿ�����,����������:   ");
					break;
				}
			}
		} while (flag == 1);
	
		printf("������ͼ������:");
		scanf("%s", ibook[n-1].name);
		printf("������ͼ������:");
		scanf("%s", ibook[n-1].type);
		
		//������Ŀд��
		if (fwrite(&ibook[n-1], sizeof(Book), 1, temp) != 1)
		{
			printf("�޷��������Ϣ!\n");
			return 0;
		}
		else
		{
			printf("%d��ͼ����Ϣ�Ѿ�����!\n", ibook[n-1].num);
			n++;
		}
		printf("����������Ϣ��?(y/n)");
		Flag = getchar();
	}
	fclose(temp);
	printf("���ͼ����Ϣִ�����!\n");
}	
