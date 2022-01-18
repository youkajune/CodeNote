#include "mytime2.h"
#include <iostream>
int main(int argc, char ** args) {
    Time t1(2, 40);
    Time t2(5, 55);
    Time t3(3, 28);
    std::cout << std::endl;
    // 没有调用复制构造函数, 也没有删除临时对象, 怀疑这里编译器有代码优化
    Time t4 = Time(t1 + t2);
    std::cout << "t4 = ";
    t4.show();
    std::cout << std::endl;
    // 同 t4
    Time t5 = t2.operator+(t3);
    std::cout << "t5 = ";
    t5.show();
    std::cout << std::endl;
    // 这里会删除临时对象
    Time t6;
    t6 = t1 + t3;
    std::cout << "t6 = ";
    t6.show();
    std::cout << std::endl;
    // 调用复制构造函数
    Time t7 = Time(t4);
    std::cout << "t7 = ";
    t7.show();
    std::cout << std::endl;


    // 3个对象相加
    std::cout << "t8: " << std::endl;
    Time t8 = t1 + t2 + t3;
    t8.show();
    std::cout << std::endl;

    std::cout << "t9: " << std::endl;
    Time t9 = (t1 + t2) + t3;
    t9.show();
    std::cout << std::endl;

    std::cout << "t10: " << std::endl;
    Time t10 = t1 + (t2 + t3);
    t10.show();
    std::cout << std::endl;
    return 0;
}