//菜单宏，用户友好为宗旨，提示信息必须要有，界面用户友好

int numCheck(char* str);
// 该函数用于检验str是否是10位全数字字符串

void adminMenu();
// 该函数打印一个管理员菜单，返回用户输入的选项
/*
功能1：显示各种菜单选项
功能2：需要用户验证管理员密码，如果是预设的密码1234即通过，否则则返回-1
功能3：验证密码完成之后才打印菜单，菜单中包含对书籍信息的增删查改选项
*/

void stuMenu();
// 该函数打印一个学生菜单，返回用户输入的选项
/*
功能1：显示各种菜单选项
功能2：需要用户输入学号，调用numCheck()函数检验学号是否合法，如果不合法则返回-1;
功能3：学号合法之后才打印菜单，菜单中包含该学生对借还表的查询，增加（即借还）功能。
*/

void mainMenu();
// 该函数打印一个主菜单，返回用户输入的选项
/*
主菜单是我们程序的主入口，是一个大菜单包含了管理员入口和学生入口
功能1：显示各种菜单选项
功能2：主菜单右上角可显示馆藏书籍的数量
*/

