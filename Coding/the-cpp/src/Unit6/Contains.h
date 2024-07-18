#ifndef CONTAINS_H_
#define CONTAINS_H_
#include <iostream>

/**
 * 这个类使用包含(组合)的方式实现 has-a 关系.
 */

class Person1 {
private:
    std::string name;
public:
    // 初始化列表中
    explicit Person1(const std::string & str = "null") : name(str) {}
    // 访问包含的类对象
    const std::string & getName() const { return name; }
    // 调用包含的类对象的公有接口
    int getSize() const { return name.size(); }
    bool operator<(const Person1 & rp) const;
    // 友元函数, 将调用包含的类对象的友元函数.
    friend std::ostream & operator<<(std::ostream & out, const Person1 & rp);
};

bool Person1::operator<(const Person1 &rp) const {
    return name < rp.name;
}

std::ostream & operator<<(std::ostream & out, const Person1 & rp) {
    out << "Name: " << rp.name;
    return out;
}
#endif // CONTAINS_H_