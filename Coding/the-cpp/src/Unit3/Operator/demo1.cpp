/*
 * 对Time类成员函数的测试
 */
#include "mytime1.h"
#include <iostream>
int main(int argc, char ** args) {
    Time t1;
    Time t2(2, 40);
    Time t3 = Time(5, 55);

    std::cout << "t1 = ";
    t1.show();
    std::cout << "t2 = ";
    t2.show();
    std::cout << "t3 = ";
    t3.show();

    t1 = t2.sum(t3);
    std::cout << "t1 + t2 = ";
    t1.show();
    return 0;
}