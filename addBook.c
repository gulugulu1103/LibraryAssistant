void addBook()
{
	FILE* fp, * temp;
	char Flag;
	Book book[1000];
	Book ibook[1000]; 
    errno_t err; // 专门用来记录错误的变量，本质是一个int
    if ((err = fopen_s(&temp,".\\.library_temp.dat", "w+")) != 0) { // failed to open the file
        printf("\t错误：无法打开.library_temp.dat，错误代码%d\n", err);
        printf("\t程序退出中...\n");
        exit(0);
    }
    printf("\t现有如下书目\n");
    listBook();
    printf("请选择是否添加书本信息(y/n):");
    Flag = getchar();
    if (Flag == 'n')
	{
		return 0;
		fclose(fp),fclose(temp);
	}
	int i = 0,flag;
	int n = countBook();
	//循环加入书目 
	while (Flag == 'y')
	{ 
		//图书编号不能重复
		printf("请输入图书编号:  ");
		do
		{
			Flag = 0;
			scanf("%d", &ibook[n-1].num);
			for (i = 0; i < n; i++)
			{
				if (book[i].num == ibook[n-1].num)
				{
					flag = 1;
					printf("该图书编号已经存在,请重新输入:   ");
					break;
				}
			}
		} while (flag == 1);
	
		printf("请输入图书名称:");
		scanf("%s", ibook[n-1].name);
		printf("请输入图书类型:");
		scanf("%s", ibook[n-1].type);
		
		//将新书目写入
		if (fwrite(&ibook[n-1], sizeof(Book), 1, temp) != 1)
		{
			printf("无法保存该信息!\n");
			return 0;
		}
		else
		{
			printf("%d号图书信息已经保存!\n", ibook[n-1].num);
			n++;
		}
		printf("继续输入信息吗?(y/n)");
		Flag = getchar();
	}
	fclose(temp);
	printf("添加图书信息执行完毕!\n");
}	
