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
}Stu;

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
//该函数显示学生模式，并提供相应选项
/*
功能1:需要用户验证，验证成功方可显示菜单选项，否则返回3；
功能2:显示菜单选项，供用户选择
*/

