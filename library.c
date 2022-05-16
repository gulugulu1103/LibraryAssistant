void addBook(FILE*fp){ // 该函数 在"library.dat"文件中追加写入一个book
    int i,n;
    int j=0;
    printf("录入图书信息\n");
    printf("输入您要录入图书的数量:");
    scanf("%d",&n);//已定义过的全局变量
    N=booknum(fp);//馆藏总数量 ,书借出也属于馆藏
    for(i=1;i<=n;i++){
        printf("\n请输入第%d本书的编号：",i);
        scanf("%d",&BOOK[j].num);
        printf("\n请输入第%d本书的名称：",i);
        scanf("%s",&BOOK[j].name);
        printf("\n该书是否已经被借阅，已被借阅输入'0',未被借阅输入'1':");
        scanf("%d",&BOOK[j].islend);
        rewind(fp);
        fwrite(&BOOK[j],size,1,fp);
        j++;
    }
    printf("信息录入完成\n");
}


void listBook(FILE*fp)//该函数遍历"library.dat"，读取book信息并打印
{
    long i;
    N=booknum(fp);
    if(N>0){
        printf("\n编号    书名        借阅状态   \n");
        fseek(fp,0L,SEEK_SET);
        fread(&BOOK[0],size,1,fp);
        for(i=1;i<=N;i++){
            printf("%-8d%-12s%-2d\n",BOOK[0].num,BOOK[0].name,BOOK[0].islend);
            fread(&BOOK[0],size,1,fp);
        }
    }else{
        printf("\n无记录。\n");
    }
}


long countBook(FILE*fp)// 该函数遍历"library.dat", 返回书本数目
{
    long begin,end,n;
    fseek(fp,0L,SEEK_SET);
    begin=ftell(fp);
    fseek(fp,size,SEEK_END);
    end=ftell(fp);
    n=(end-begin)/size-1;
    return n;
}


void delBook(FILE*fp){// 该函数调用listBook()，随后接收用户的序号来删除书目
    FILE*fp1;
    int number,i,j,c,k;
    N=booknum(fp);
    struct book *p=BOOK;
    printf("\n输入您要删除图书的数量：");
    scanf("%d",&c);
    for(k=1;k<=c;k++){
        printf("\n输入你想要删除的图书的书号：");
        scanf("%d",&number);
        rewind(fp);
        fread(p,size,N,fp);
    for(i=0;i<N;i++){
        if(BOOK[i].num==number){
           break;
        }
    }
    for(j=i;j<N-1;j++){//书的信息改变
        BOOK[j].num=BOOK[j+1].num;
        strcpy(BOOK[j].name,BOOK[j+1].name);
        BOOK[j].islend=BOOK[j+1].islend;
        strcpy(BOOK[j].stu1,BOOK[j+1].stu1);
        strcpy(BOOK[j].stu2,BOOK[j+1].stu2);
    }
        N=N-1;
        printf("\n删除成功\n");
        fp1=fopen("library.dat","wb+");
        rewind(fp1);
        fwrite(p,size,N,fp1);
        fclose(fp1);
    }
}


void editbook(FILE*fp){//该函数调用listBook(), 随后接收用户的序号来修改书目
    FILE*fp1;
    struct book *p=BOOK;
    int number;//表示要修改的书号
    int i,islend;
    printf("\n输入你想要修改的图书的书号：") ;
    scanf("%d",&number);
    N=booknum(fp);
    rewind(fp);
    fread(p,size,N,fp);
    for(i=0;i<N;i++){
        if(BOOK[i].num==number){
            printf("\n现在请输入新的信息：\n");
            printf("请输入书的新的书号：");
            scanf("%d",&BOOK[i].num);
            printf("\n请输入书的新的名称：");
            scanf("%s",&BOOK[i].name);
            printf("\n请输入书的新状态：");
            scanf("%d",&BOOK[i].islend);
            break;
        }
    }
    if(i>N) printf("\n您输入的书号不存在\n");
    else printf("\n修改成功\n");
    fp1=fopen("library.dat","wb+");
    rewind(fp1);
    fwrite(p,size,N,fp1);
    fclose(fp1);
}
