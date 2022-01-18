#ifndef CONST_OBJECT_H_
#define CONST_OBJECT_H_
#include <string>
#include <iostream>
// const 成员函数
class Demo {
private:
    int value;
    std::string id;
public:
    Demo();
    Demo(int, std::string);
    ~Demo();
    void show() const;
    const Demo& max(const Demo &) const;
};
Demo::Demo() {
    value = 0;
    id = "no authenciation_id";
}

Demo::Demo(int v, std::string s) {
    value = v;
    id = s;
}

Demo::~Demo() {
    std::cout << "Class Demo's Destructor." << std::endl;
}

void Demo::show() const {
    std::cout << "Value is " << value << ". ID is " << id << std::endl;
}

const Demo& Demo::max(const Demo & d) const{
    if (d.value > value)
        return d;
    return *this;
}
#endif // CONST_OBJECT_H_