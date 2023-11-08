#ifndef VECTOR_H
#define VECTOR_H

#include <iostream>
#include <vector>
const int NUM = 5;

/**
 * vector ��ʾС����
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
 * ��ʾ vector ������һЩ������ size() begin() end() push_back() erase() insert()
 **/
struct Book {
    std::string bookName; // ����
    double rating; // ����
};

/**
 * ���� < �����
 **/
bool operator<(Book & r1, Book & r2);

bool compareBook(Book & r1, Book & r2);

/**
 * ����������� Book ��Ϣ
 *  @return True-����������Ϣ��False-�������
 **/
bool fillBook(Book & rb);

/**
 * ��ӡ����� Book ����Ϣ
 **/
void showBook(const Book & rb);

void test_vector_func() {
    std::vector<Book> books; // Ԫ������Ϊ Book ��ʸ��
    Book tmp; // ���ڱ���������Ϣ�� Book ����
    while (fillBook(tmp)) {
        books.push_back(tmp); // �� vector ��β�����Ԫ��
    }
    int num = books.size(); // ��ȡ vector ������Ԫ�ص���Ŀ
    if (num > 0) {
        std::cout << "Thank you. You entered the following:\n" << "BookName\tBook\n";

        for (int i = 0; i < num; ++i) { // ʹ����������
            showBook(books[i]);
        }

        std::cout << "Using iterator:\n";
        std::vector<Book>::iterator it;
        for (it = books.begin(); it != books.end(); it++) { // ʹ�õ���������
            showBook(*it);
        }

        // ���������� books ����һϵ����ɾ�������ȱ���һ�����е� books �ĸ������ٽ�����ɾ������
        std::vector<Book> oldList(books); // ʹ�� vector<Book> �ĸ��ƹ��캯��������һ�� books �ĸ���

        if (num > 3) {
            // ɾ�� books �� [�ڶ���Ԫ��, ���ĸ�Ԫ��)
            books.erase(books.begin()+1, books.begin()+3);
            std::cout << "After erase:\n"; // ��ӡɾ��Ԫ��֮��� books
            for (it = books.begin(); it != books.end(); it++) {
                showBook(*it);
            }

            // �� books �ĵ�һ��Ԫ��֮ǰ��� oldList �� [�ڶ���Ԫ��, ������Ԫ��)����ֻ���� oldList �ĵڶ���Ԫ��
            books.insert(books.begin(), oldList.begin()+1, oldList.begin()+2);
            std::cout << "After insert:\n";
            for (it = books.begin(); it != books.end(); it++) {
                showBook(*it);
            }
        }

        books.swap(oldList); // ���� books �� oldList �е�Ԫ��
        std::cout << "Swapping books with oldList:\n";
        for (it = books.begin(); it != books.end(); it++) {
            showBook(*it);
        }
    } else {
        std::cout << "Books is null.\n";
    }
}

/**
 * ��ʾ STL �� for_each()/random_stuffle()/sort()
 **/
void test_vector_algo() {
    std::vector<Book> books;
    Book temp;

    while(fillBook(temp))
        books.push_back(temp);

    if (books.size()) {
        std::cout << "Thank you. You entered the following:\n" << "BookName\tBook\n";
        std::for_each(books.begin(), books.end(), showBook);

        std::sort(books.begin(), books.end()); // ��һ���汾�� sort
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
    if (!std::cin) // ������õ��� cin �� operator!() �������ȼ��� std::cin.fail()
        return false;
    while (std::cin.get() != '\n') // ȥ������Ļ��з�
        continue;
    return true;
}

void showBook(const Book & rb) {
    std::cout << rb.bookName << " " << rb.rating << std::endl;
}


#endif //VECTOR_H