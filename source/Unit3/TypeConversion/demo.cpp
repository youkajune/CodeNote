#include "stone.h"
// 转换构造函数的测试
void testConstructorConvert() {
    Stone s1;
    s1 = Stone(27.3); // 显式调用构造函数
    s1.show_lbs();
    s1 = (Stone) 25.3; // 显式类型转换 or 强制类型转换
    s1.show_lbs();
//    s1 = 24.Unit5; // 隐式类型转换 or 自动类型转换, 使用 explicit 修饰构造函数之后将报错
//    s1.show_lbs();

    Demo d1 = 23.8;
    s1 = d1;
    s1.show_lbs();
}
// 转换函数的测试
void testConvert() {
    Stone s1 = Stone(23.9);
    double pound = (double) s1;
    std::cout << "Convert to double => " << pound << std::endl;
    std::cout << "Stone Object: " << double(s1)  << std::endl; // 将转换为 double
}

int main(int argc, char ** args) {
    testConvert();
    return 0;
}