#ifndef PRIVATEEXTEND_H_
#define PRIVATEEXTEND_H_
#include <iostream>
/**
 * 这个使用私有继承的方式实现 has-a 关系.
 */
class Person2 : private std::string {
public:
    // 初始化列表中显式调用基类的构造函数.
    explicit Person2(const std::string & str = "null") : std::string(str) {}
    // 访问基类对象
    const std::string & getName() const { return (const std::string &) *this; }
    // 调用基类函数
    int getSize() const { return std::string::size(); }
    bool operator<(const Person2 & rp) const;
    // 友元函数, 将调用基类的友元函数.
    friend std::ostream & operator<<(std::ostream & out, const Person2 & rp);
};

bool Person2::operator<(const Person2 &rp) const {
    return (std::string) *this < (std::string) rp;
}

std::ostream & operator<<(std::ostream & out, const Person2 & rp) {
    out << "Name: " << (std::string) rp;
    return out;
}

#endif // PRIVATEEXTEND_H_