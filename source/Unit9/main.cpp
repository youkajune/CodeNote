#include <ctime>
#include "RTTI.h"

/**
 * 随机生成 Grand、Superb、Magnificent 三个类中的某个类的对象
 **/
Grand *GetOne() {
    Grand * p;
    int temp = std::rand();
    switch (temp % 3) {
        case 0:
            p = new Grand(temp);
            break;
        case 1:
            p = new Superb(temp);
            break;
        case 2:
            p = new Magnificent(temp, 'A' + temp % 26);
            break;
        default:
            p = nullptr;
    }
    return p;
}

/**
 * RTTI dynamic_cast 运算符的演示程序
 **/
void test_dynamic_cast_1() {
    Grand * pg;
    Superb * ps;
    std::srand(std::time(0));
    for (int i = 0; i < 5; ++i) {
        pg = GetOne();
        if (pg != nullptr)
            pg->Speak();
        if (ps = dynamic_cast<Superb *> (pg))
            ps->Say();
        delete pg;
    }
}

/**
 * RTTI dynamic_cast 运算符的演示程序, 添加了 name() 的演示
 **/
void test_dynamic_cast_2() {
    Grand * pg;
    Superb * ps;
    std::srand(std::time(0));
    for (int i = 0; i < 5; ++i) {
        pg = GetOne();
        if (pg != nullptr) {
            std::cout << "Now type is " << typeid(*pg).name() << ".\n";
            pg->Speak();
        }
        if (ps = dynamic_cast<Superb *> (pg))
            ps->Say();
        if (typeid(Magnificent) == typeid(*pg))
            std::cout << "This is a Magnificent.\n";
        delete pg;
    }
}

/**
 * RTTI 误用的例子：typeid 应该用于 dynamic_cast 和虚函数无法使用的场景，而不是替代 dynamic_cast，下面演示下不推荐的用法
 **/
void test_dynamic_cast_3() {
    Grand * pg;
    Superb * ps;
    Magnificent * pm;
    std::srand(std::time(0));
    for (int i = 0; i < 5; ++i) {
        pg = GetOne();
        if (typeid(Grand) == typeid(*pg)) {
            pg->Speak();
        } else if (typeid(Superb) == typeid(*pg)) {
            ps = (Superb *) pg;
            ps->Speak();
            ps->Say();
        } else if (typeid(Magnificent) == typeid(*pg)) {
            pm = (Magnificent *) pg;
            pm->Speak();
            pm->Say();
        }
        delete pg;
    }
}

/**
 * 修改常量指针所指向的常量值
 **/
void change(const int * pInt, int n) {
    int * p = const_cast<int *> (pInt);
    *p += n;
}

/**
 * const_cast 运算符的测试
 **/
void test_const_cast() {
    int i1 = 3333;
    const int i2 = 2000;

    std::cout << "i1, i2: " << i1 << ", " << i2 << std::endl;

    change(&i1, -100);
    change(&i2, -100);

    std::cout << "i1, i2: " << i1 << ", " << i2 << std::endl;
}

int main() {
//    test_dynamic_cast_1();
//    test_dynamic_cast_2();
//    test_dynamic_cast_3();
    test_const_cast();
    return 0;
}