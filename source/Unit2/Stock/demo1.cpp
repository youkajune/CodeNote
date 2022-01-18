#include "stock1.h"
/*
 * 演示构造函数和析构函数的使用,包括复制构造函数的使用时机.
 */
Stock f1(Stock s1);
Stock& f2(Stock &s1);

int main(int argc, char** args) {
    // 显示调用构造函数
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "显式调用构造函数" << std::endl;
    Stock s1 = Stock("可口可乐", 300, 1.25);
    Stock s2 = Stock{"茅台", 540, 3.7};
    std::cout << "-------------------------------------" << std::endl << std::endl;

    // 隐式调用构造函数
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "隐式调用构造函数" << std::endl;
    Stock s3("宁德时代", 1030, 4.8);
    Stock s4 = {"药明康德", 680, 2.75};
    std::cout << "-------------------------------------" << std::endl << std::endl;

    // new 搭配构造函数
    Stock* p1 = new Stock("比亚迪", 500, 3.8);

//    Stock s5; // 没有提供默认构造函数时会报错
//    Stock s6; // 提供了默认构造函数，并不会报错

    // 没有定义复制构造函数时也可以使用，不会报错
    std::cout << "-------------------------------------" << std::endl;
    std::cout << "复制构造函数演示" << std::endl;
    Stock s7 = Stock(s1);
    s7.show();
    std::cout << std::endl;
    Stock s8 = s1;
    s8.show();
    s8 = s2; // 注意!!! 这里是赋值运算符,和赋值构造函数无关,因为这个是赋值,不是初始化
    s8.show();
    std::cout << "-------------------------------------" << std::endl << std::endl;

    std::cout << std::endl;
    std::cout << "-------------------------------------" << std::endl;
    f1(s1);
    std::cout << std::endl;
    f2(s1);
    std::cout << "-------------------------------------" << std::endl << std::endl;
    delete p1;
    return 0;
}

Stock f1(Stock s1) {
    std::cout << "f1()" << std::endl;
//    s1.show();
    return s1;
}

Stock& f2(Stock &s1) {
    std::cout << "f2()" << std::endl;
//    s1.show();
    return s1;
}