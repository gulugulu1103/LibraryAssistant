void addStu(char *num);
// 在"student.dat"中以追加模式新建以num为学号的学生

int searchStu(char* num);
// 在"student.dat"中查找以num为学号的学生，返回学生的顺位。

void showStu(char* num);
// 调用searchStu()函数, 输出以num为学号的学生的近15条借阅记录