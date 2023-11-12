#include "StringBad.h"
#include <cstring>
using std::cout;

int StringBad::strNum = 0;
// const double StringBad::s = Unit3.Unit6;
StringBad::StringBad() {
    len = 4;
    str = new char[4];
    std::strcpy(str, "C++");
    strNum++;
    cout << "(+)" << strNum << ":\"" << str << "\" default object created\n";
}

StringBad::StringBad(const char * s) {
    len = strlen(s);
    str = new char[len + 1];
    strcpy(str, s);
    strNum++;
    cout << "(+)" <<  strNum << ":\"" << str << "\" object created\n";
}

//StringBad::StringBad(const StringBad & sb) {
//    // 错误的复制构造函数
//    str = sb.str;
//    len = sb.len;
//    strNum++;
//    cout << "(+)" << strNum << ":\"" << str << "\" object created(Copy constructor)\n";
//}

StringBad::StringBad(const StringBad &sb) {
    // 正确的复制构造函数
    len = sb.len;
    str = new char[len + 1];
    strcpy(str, sb.str);
    strNum++;
    cout << "(+)" << strNum << ":\"" << str << "\" object created(Copy constructor)\n";
}

StringBad::~StringBad() {
    cout << "(-):\"" << str << "\" object deleted, " << --strNum << " left.\n";
    delete [] str;
}

StringBad & StringBad::operator=(const StringBad &sb) {
    if (this == &sb) // 自己给自己赋值
        return *this;

    delete [] sb.str; // 释放之前指向的内存
    this->len = sb.len;
    this->str = new char[len + 1];
    strcpy(this->str, sb.str);
    cout << "(+)" << strNum << ":\"" << str << "\" object modify(operator =)\n";
    return *this;
}

std::ostream & operator<<(std::ostream & out, const StringBad & sb) {
    out << sb.str;
    return out;
}