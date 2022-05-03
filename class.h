// 这里放着所有对象

typedef struct {
    // 一本书
    char name[81];
    char type[81];
} Book;

typedef struct {
    // 一条记录
    Book book;
    char time[81];
    int borrow;  // borrow = 1 是借出, borrow = 0 是归还
    Rec* next;
} Rec;

typedef struct {
    // 学生
    char num[81];
    Rec* head;s
} Stu;
