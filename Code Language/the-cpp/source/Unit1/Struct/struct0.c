// 演示结构体的声明、定义变量、变量初始化、变量赋值
#include <stdio.h>
struct book {
    char title[100];
    char author[80];
    float value;
};

void show_book(struct book* ptr_book) {
    printf("This book\'s name is %s, the author is %s, the value is %lf.\n",
           ptr_book->title, ptr_book->author, ptr_book->value);
    printf("The struct value\'s address is %p.\n", ptr_book);
    printf("The title\'s address is %p.\n", ptr_book->title);
    printf("The author\'s address is %p.\n", ptr_book->author);
    printf("-------------------------------------------------------------\n");
}

int main(int argc, char** args) {
    printf("The size of struct book is %x.\n", sizeof (struct book));
    struct book b1 = {
            "C Primer",
            "Stephen Prata",
            68.3
    };
    struct book b2 = b1;
    show_book(&b1);
    show_book(&b2);
}