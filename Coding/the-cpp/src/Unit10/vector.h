#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>
const int NUM = 5;

/**
 * vector 演示小程序
 **/
void test_vector() {
    std::vector<int> vi(NUM);
    std::vector<std::string> vs(NUM);

    for (int i = 0; i < NUM; ++i) {
        std::cout << "Please input a int and then input a string:\n";
        std::cin >> vi[i];
        std::cin.get();
        std::getline(std::cin, vs[i]);
    }

    std::cout << "Thank you.\n\n";

    for (int i = 0; i < NUM; ++i) {
        std::cout << vi[i] << " " << vs[i] << std::endl;
    }
}

/**
 * 演示 vector 容器的一些方法： size() begin() end() push_back() erase() insert()
 **/
struct Book {
    std::string bookName; // 书名
    double rating; // 评分
};

/**
 * 重载 < 运算符
 **/
bool operator<(Book & r1, Book & r2);

bool compareBook(Book & r1, Book & r2);

/**
 * 根据输入填充 Book 信息
 *  @return True-继续输入信息，False-输入结束
 **/
bool fillBook(Book & rb);

/**
 * 打印传入的 Book 的信息
 **/
void showBook(const Book & rb);

void test_vector_func() {
    std::vector<Book> books; // 元素类型为 Book 的矢量
    Book tmp; // 用于保存输入信息的 Book 对象
    while (fillBook(tmp)) {
        books.push_back(tmp); // 在 vector 的尾部添加元素
    }
    int num = books.size(); // 获取 vector 容器中元素的数目
    if (num > 0) {
        std::cout << "Thank you. You entered the following:\n" << "BookName\tBook\n";

        for (int i = 0; i < num; ++i) { // 使用索引访问
            showBook(books[i]);
        }

        std::cout << "Using iterator:\n";
        std::vector<Book>::iterator it;
        for (it = books.begin(); it != books.end(); it++) { // 使用迭代器访问
            showBook(*it);
        }

        // 接下来将对 books 进行一系列增删操作，先保存一个现有的 books 的副本，再进行增删操作。
        std::vector<Book> oldList(books); // 使用 vector<Book> 的复制构造函数创建了一个 books 的副本

        if (num > 3) {
            // 删除 books 的 [第二个元素, 第四个元素)
            books.erase(books.begin()+1, books.begin()+3);
            std::cout << "After erase:\n"; // 打印删除元素之后的 books
            for (it = books.begin(); it != books.end(); it++) {
                showBook(*it);
            }

            // 向 books 的第一个元素之前添加 oldList 的 [第二个元素, 第三个元素)，即只插入 oldList 的第二个元素
            books.insert(books.begin(), oldList.begin()+1, oldList.begin()+2);
            std::cout << "After insert:\n";
            for (it = books.begin(); it != books.end(); it++) {
                showBook(*it);
            }
        }

        books.swap(oldList); // 交换 books 与 oldList 中的元素
        std::cout << "Swapping books with oldList:\n";
        for (it = books.begin(); it != books.end(); it++) {
            showBook(*it);
        }
    } else {
        std::cout << "Books is null.\n";
    }
}

/**
 * 演示 STL 的 for_each()/random_stuffle()/sort()
 **/
void test_vector_algo() {
    std::vector<Book> books;
    Book temp;

    while(fillBook(temp))
        books.push_back(temp);

    if (books.size()) {
        std::cout << "Thank you. You entered the following:\n" << "BookName\tBook\n";
        std::for_each(books.begin(), books.end(), showBook);

        std::sort(books.begin(), books.end()); // 第一个版本的 sort
        std::cout << "After sorted by operator<:\n";
        std::for_each(books.begin(), books.end(), showBook);

        std::sort(books.begin(), books.end(), compareBook);
        std::cout << "After sorted by compareBook:\n";
        std::for_each(books.begin(), books.end(), showBook);

        std::random_shuffle(books.begin(), books.end());
        std::cout << "After sorted by random_stuffle:\n";
        std::for_each(books.begin(), books.end(), showBook);
    } else {
        std::cout << "No books.\n";
    }
}

bool operator<(Book & r1, Book & r2){
    if (r1.bookName < r2.bookName)
        return true;
    else if (r1.bookName == r2.bookName && r1.rating < r2.rating)
        return true;
    else
        return false;
}

bool compareBook(Book & r1, Book & r2) {
    return r1.rating < r2.rating;
}

bool fillBook(Book & rb) {
    std::cout << "Enter book name(quit to quit): ";
    std::getline(std::cin, rb.bookName);
    if ("quit" == rb.bookName)
        return false;
    std::cout << "Enter book rating: ";
    std::cin >> rb.rating;
    if (!std::cin) // 这里调用的是 cin 的 operator!() 方法，等价于 std::cin.fail()
        return false;
    while (std::cin.get() != '\n') // 去掉多余的换行符
        continue;
    return true;
}

void showBook(const Book & rb) {
    std::cout << rb.bookName << " " << rb.rating << std::endl;
}


#endif //VECTOR_H