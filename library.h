
void addBook();
// 该函数 在"library.dat"文件中追加写入一个book

void listBook();
// 该函数遍历"library.dat"，读取book信息并打印

int countBook();
// 该函数遍历"library.dat", 返回书本数目

void delBook();
// 该函数调用listBook()，随后接收用户的序号来删除书目

void editBook();
// 该函数调用listBook(), 随后接收用户的序号来修改书目