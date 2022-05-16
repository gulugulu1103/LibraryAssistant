//菜单宏，用户友好为宗旨，提示信息必须要有，界面用户友好

int mainMenu(){
     int choice;
     printf("\t\t欢迎光临图书管理系统\n");
     printf("\t1.管理员模式\n");
     printf("\t2.学生模式\n");
     printf("\t3.退出系统\n");
     printf("\n\t请输入您的选择：");
     scanf("%d",&choice);
     return choice;
    }


    system("cls");
    printf("当前馆藏书数量:%d\n",booknumber);
    printf("      图书馆管理系统      ");
    printf("\n");
    printf("Library Management System\n");
    printf("\n");
    printf("1.学生入口\n");
    printf("2.管理员入口\n");
    int num;   //用户输入的选项
    if(scanf_s("%d",&num)== 1)
    {
        printf("您已进入学生入口.\n");
        system("pause");
        fflush(stdin);//清空缓冲区
        num = 1;
        return num;
    }else{
        printf("您已进入管理员入口.\n");
        system("pause");
        fflush(stdin);//清空缓冲区
        num = 2;
        return num;
    }
};
// 该函数打印一个主菜单，返回用户输入的选项
/*
主菜单是我们程序的主入口，是一个大菜单包含了管理员入口和学生入口
功能1：显示各种菜单选项
功能2：主菜单右上角可显示馆藏书籍的数量
*/
char PIN[20]="1234";
//管理员模式的密码验证
int PIN_verify(){
        char code[20];//存放你输入的密码
    printf("\t  欢迎使用管理员模式\n");
    printf("\t 请输入密码：");
    scanf("%s",&code);
    if(!strcmp(code,PIN)){//比较输入的密码与原密码是否一样
        printf("\t  成功进入管理员模式\n");
        system("pause");
        return 1;
    }else{
        printf("\t  密码错误");
        system("pause");
    return 0;
 }


int adminMenu();
{
    int choice;
    printf("\n\t       管理员模式\n");
    printf("\t 1.录入图书信息 2.修改图书信息\n");
    printf("\t 3.删除图书信息 4.查阅单个学生的借阅记录\n") ;
    printf("\t 5.查看所有图书信息 6.录入学生信息\n") ;
    printf("\t 7.返回首页\n");
    printf("\t请输入您的选择：");
    scanf("%d",&choice);
    printf("\n");
    return choice;
}

// 该函数打印一个管理员菜单，返回用户输入的选项
/*
功能1：显示各种菜单选项
功能2：需要用户验证管理员密码，如果是预设的密码1234即通过，否则则返回-1
功能3：验证密码完成之后才打印菜单，菜单中包含对书籍信息的增删查改选项
*/

int numCheck(char* str);
// 该函数用于检验str是否是10位全数字字符串

int stuMenu(){
    typedef struct {
        // 学生
        
        char num[81];
        Rec rec[21]; // 借还记录数组
        int recNum; // 借还记录数量
    } Stu;

}
    
    struct student{
        char ID[20];
        char secret[20];
    }infor[MAXN];
    int NUM=0;
    void stu_infor(FILE*fp2){
     int i,num;
     int j=0;
     printf("\n请输入你要录入的学生数量：");
     scanf("%d",&num);
     S=stu_num(fp2);
     printf("\n开始录入\n");
     for(i=1;i<=num;i++){
      printf("\n请输入第%d个学生的信息\n\n",i);
      printf("\t账号：");
      scanf("%s",&infor[j].ID);
      printf("\t密码：");
      scanf("%s",&infor[j].secret);
      rewind(fp2);
      fwrite(&infor[j],size1,1,fp2);
      j++;
     }

// 该函数打印一个学生菜单，返回用户输入的选项
/*
功能1：显示各种菜单选项
功能2：需要用户输入学号，调用numCheck()函数检验学号是否合法，如果不合法则返回-1;
功能3：学号合法之后才打印菜单，菜单中包含该学生对借还表的查询，增加（即借还）功能。
*/
int student(FILE*fp2){
    int choice;
    printf("\n\t  欢迎使用学生模式\n");
         if(STU_verify(fp2)){
             printf("\t 1-借阅图书   2-还书   3-返回首页\n") ;
             printf("\t请输入您的选择:");
             scanf("%d",&choice);
             return choice;
         }else{
             printf("\n信息库里没有您的信息\n");
             return 3;
              }
        }
        

