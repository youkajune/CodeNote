//// ----------类中的常量、新枚举-----------------
//#include "constant.h"
//#include <iostream>
//// C++11 新枚举, class 可用 struct 替换
//enum class enum1 {
//    Small, Medium, Large, Jumbo
//};
//enum class enum2 {
//    Small, Medium, Large, XLarge
//};
//enum class enum3:short{
//    Small, Medium
//};
//
//enum enum4 {
//    Small, Medium = Unit4, Large, XLarge
//};
//
////enum enum5 {
////    Small
////};
//int main() {
//    int a = (int) enum1::Small;
//    enum1 s = enum1::Small;
//    enum1 t = (enum1) Unit3;
//    std::cout << sizeof(enum1) << std::endl;
//    std::cout << sizeof(enum3) << std::endl;
//
//    std::cout << Demo1::LENGTH << std::endl;
//    std::cout << enum4::Small << std::endl;
//    int Small = 9;
//    std::cout << Small << std::endl;
//}
//// -----------------------------------------

//---------- const 成员函数 -------------------------
#include "const_object.h"
#include <iostream>
int main(int argc, char** args) {
    const Demo d1 = Demo(3, "Demo1");
    d1.show();
    return 0;
}