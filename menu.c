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
// 该函数打印一个主菜单，返回用户输入的选项。（主菜单）
/*
主菜单是我们程序的主入口，是一个大菜单包含了管理员入口和学生入口。
功能1：显示各种菜单选项；
功能2：主菜单右上角可显示馆藏书籍的数量。
*/


char PIN[20]="1234";
int PIN_verify(){
        char code[20];
    printf("\t  欢迎使用管理员模式\n");
    printf("\t 请输入密码：");
    scanf("%s",&code);
    if(!strcmp(code,PIN)){
        printf("\t  成功进入管理员模式\n");
        system("pause");
        return 1;
    }else{
        printf("\t  密码错误");
        system("pause");
    return 0;
 }
//管理员模式的密码验证。（管理员模式密码验证）
/*
功能1：存放用户输入的密码；
功能2：比较输入的密码与原密码是否匹配。
*/


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
// 该函数打印一个管理员菜单，返回用户输入的选项。（管理员模式菜单）
/*
功能1：显示各种菜单选项；
功能2：需要用户验证管理员密码，如果是预设的密码1234即通过，否则则返回-1；
功能3：验证密码完成之后才打印菜单，菜单中包含对书籍信息的增删查改选项。
*/


int numCheck(char* str);
    while(1){
        scanf("%s",str);
        if(strspn(str,"0123456789")!=strlen(str)){
            printf("请输入有效数字:\t\t\t");
            rewind(stdin);
            continue;
        }else{
            break;
        }
    }
// 该函数用于检验str是否是10位全数字字符串。（检查字符串）
/*
功能1：判断输入的是否全部是数字，如果不是数字，提示循环输入；
功能2：当输入的是数字时，则停止循环。
*/


int stuMenu(){
    typedef struct {
        // 学生
    char num[81];
    Rec rec[21]; // 借还记录数组
    int recNum; // 借还记录数量
    }Stu;
    int STU_verify(FILE*fp2){
    int i;
    char id[20];
    char password[20];
    struct student *p=infor;
    S=Stu_num(fp2);
    printf("\n请输入您的ID:");
    scanf("%s",&id);
    printf("\n请输入你的密码：");
    scanf("%s",&password);
    rewind(fp2);
    fread(p,size1,S,fp2);
    for(i=0;i<S;i++){
        if(strcmp(id,infor[i].id)==0 && strcmp(password,infor[i].secret)==0){
            printf("成功进入学生模式\n");
            system("pause");
            return 1;
        }else{
            printf("\nid或者密码错误\n");
            system("pause");
            return -1;
        }
    }
}
// 该函数打印一个学生菜单，返回用户输入的选项。（学生模式密码验证）
/*
功能1：显示各种菜单选项
功能2：需要用户输入学号，调用numCheck()函数检验学号是否合法，如果不合法则返回-1;
功能3：学号合法之后才打印菜单，菜单中包含该学生对借还表的查询，增加（即借还）功能。(弄不来了）
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
//该函数显示学生模式，并提供相应选项。（学生模式菜单）
/*
功能1:需要用户验证，验证成功方可显示菜单选项，否则返回3；
功能2:显示菜单选项，供用户选择。
 */
