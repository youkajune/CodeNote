#include <new>
#include <iostream>
//#include <string>

struct book{
    char name[20];
    double price;
};
char buffer1[100];
char buffer2[100];

class TestType {
public:
    TestType(const std::string & s = "Just use to test", int number = 0) {
        words = s;
        this->number = number;
        std::cout << words << " constructed.\n";
    }
    ~TestType() {
        std::cout << words << " destructed.\n";
    }
    friend std::ostream & operator<<(std::ostream & out, const TestType & t);
private:
    std::string words;
    int number;
};

std::ostream & operator<<(std::ostream & out, const TestType & t) {
    std::cout << t.words << ", " << t.number;
    return out;
}

// 对内置类型以及结构体变量使用 new 定位运算符
void useNewPosition1();
// 对类对象使用 new 定位运算符
void useNewPosition2();

int main() {
    std::cout << "useNewPosition1(): " << std::endl;
    useNewPosition1();
    std::cout << std::endl;
    std::cout << "useNewPosition2(): " << std::endl;
    useNewPosition2();
    return 0;
}

void useNewPosition1() {
    std::cout << "buffer1 address: " << (void *) buffer1 << std::endl;
    std::cout << "buffer2 address: " << (void *) buffer2 << std::endl;
    book *p1, *p2;
    p1 = new book;
    // 定位 new 运算符，在 buffer1 的位置上创建一个 book 结构的变量
    p2 = new (buffer1) book;
    std::cout << "p1 address: " << p1 << std::endl;
    std::cout << "p2 address: " << p2 << std::endl;
    int * p3 = new (buffer2) int[10];
    std::cout << "p3 address: " << p3 << std::endl;
}

void useNewPosition2() {
    char * buffer = new char[512];
    std::cout << "Memory address: " << (void *) buffer << std::endl;

    TestType * p1, *p2, *p3, *p4;
    p1 = new (buffer) TestType;
    p2 = new TestType("Heap1", 20);
    std::cout << "buffer(p1) address: " << p1 << std::endl;
    std::cout << "heap(p2)  address: " << p2 << std::endl;
    std::cout << "Memory content:\n";
    std::cout << p1 << ": " << *p1 << "; " << p2 << ": " << *p2 << std::endl << std::endl;

    // 错误, 这样创建对象会覆盖 p1 指向的对象. 如果类动态为成员分配内存, 会导致内存泄漏.
//    p3 = new (buffer) TestType("Bad", Unit6);
    p3 = new (buffer + sizeof (TestType)) TestType("Bad", 6);
    p4 = new TestType("Heap2", 10);
    std::cout << "Memory content:\n";
    std::cout << p3 << ": " << *p3 << "; " << p4 << ": " << *p4 << std::endl << std::endl;

    std::cout << "p1: " << *p1 << std::endl << std::endl;

    delete p2;
    p2 = nullptr;
    delete p4;
    p4 = nullptr;
    p3->~TestType();
    p3 = nullptr;
    p1->~TestType();
    p1 = nullptr;
    delete [] buffer;
    std::cout << "Finish.\n";
}
