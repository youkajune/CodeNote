#include "String.h"
#include <cstring>
int String::strNum = 0;
// implements constructors
String::String() {
    len = 3;
    str = new char[len + 1];
    strcpy(str, "C++");
    strNum++;
    std::cout << "(+)" << strNum << ":\"" << str << "\" default object created\n";
}

String::String(char * p) {
    len = strlen(p);
    str = new char[len + 1];
    strcpy(str, p);
    strNum++;
    std::cout << "(+)" <<  strNum << ":\"" << str << "\" object created\n";
}

String::String(const String & s) {
    len = s.len;
    str = new char[len + 1];
    strcpy(str, s.str);
    strNum++;
    std::cout << "(+)" << strNum << ":\"" << str << "\" object created(Copy constructor)\n";
}

// implements destructors
String::~String() {
    std::cout << "(-):\"" << str << "\" object deleted, " << --strNum << " left.\n";
    delete [] str;
}

// implements overload operator methods
String & String::operator=(String & s) {
    if (this == &s)
        return *this;

    delete [] this->str;
    this->len = s.len;
    this->str = new char[len + 1];
    strcpy(str, s.str);
    std::cout << "(+)" << strNum << ":\"" << str << "\" object modify(operator =)\n";
    return *this;
}

String & String::operator=(const char * p) {
    delete [] this->str;

    this->len = strlen(p);
    this->str = new char[len + 1];
    strcpy(str, p);
    std::cout << "(+)" << strNum << ":\"" << str << "\" object modify(operator =)\n";
    return *this;
}

char & String::operator[](int index) {
    return str[index];
}

const char & String::operator[](int index) const {
    return str[index];
}

// implements overload operator friends
bool operator<(const String & s1, const String & s2) {
    if (strcmp(s1.str, s2.str) < 0)
        return true;
    return false;
}

bool operator>(const String & s1, const String & s2) {
    return s2 < s1;
}

bool operator==(const String & s1, const String & s2) {
    return strcmp(s1.str, s2.str) == 0;
}

std::ostream & operator<<(std::ostream & out, const String & s) {
    out << s.str;
    return out;
}

std::istream & operator>>(std::istream & is, String & s) {
    char temp[40];
    std::cin.get(temp, 40);

    // 赋值
    if (is) s = temp;
    // 清除无效字符
    while(is && is.get() != '\n') continue;

    return is;
}
// member function

// static member function
int String::HowMany() {
    return strNum;
}