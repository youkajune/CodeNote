// 深拷贝演示
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct book {
    char *title;
    char *author;
    float value;
};

void show_book(const struct book* ptr_book) {
    printf("This book\'s name is %s, the author is %s, the value is %lf.\n",
           ptr_book->title, ptr_book->author, ptr_book->value);
    printf("The struct value\'s address is %p.\n", ptr_book);
    printf("The title\'s address is %p.\n", ptr_book->title);
    printf("The author\'s address is %p.\n", ptr_book->author);
    printf("-------------------------------------------------------------\n");
}

void free_book(struct book* ptr_b) {
    if (ptr_b == NULL)
        return;
    if(ptr_b->title != NULL) {
        free(ptr_b->title);
        ptr_b->title = NULL;
    }
    if (ptr_b->author != NULL) {
        free(ptr_b->author);
        ptr_b->title = NULL;
    }
    printf("Free Memory Success!\n");
}

void copy_book(struct book * dest, const struct book * src) {
    // 如果dest的指针成员正指向一个动态分配的内存，首先将其释放掉，防止内存泄漏
    if(dest != NULL)
        free_book(dest);

    // 动态分配能够存储src对应成员的内存
    dest->title = malloc(strlen(src->title) + 1);
    dest->author = malloc(strlen(src->author) + 1);

    // 赋值
    strcpy(dest->title, src->title);
    strcpy(dest->author, src->author);
    dest->value = src->value;
}

int main(int argc, char** args) {
    // 初始化 b1 变量
    struct book b1 = {.value = 68.3};
    b1.title = (char*) malloc(9 * sizeof (char));
    strcpy(b1.title, "C Primer");
    b1.author = (char*) malloc(13 * sizeof (char));
    strcpy(b1.author, "Stephen Prata");
    // 展示 b1 的成员
    show_book(&b1);
    // 声明 b2, 并将 b1 赋值给 b2
    struct book b2;
    copy_book(&b2, &b1);
    // 展示 b2 的成员
    show_book(&b2);

    // 修改 b2 的 author 成员指向的内容
    strcpy(b2.author, "You Ka");
    // 展示 b2 的成员
    show_book(&b2);
    // 展示 b1 的成员
    show_book((&b1));

    // 释放 b1 动态分配的内存
    free_book(&b1);
    // 释放 b2 动态分配的内存，此时不会崩溃
    free_book(&b2);
    return 0;
}