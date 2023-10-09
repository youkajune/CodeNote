#ifndef DEMO_H_
#define DEMO_H_

#include <iostream>
/**
 * 为了演示栈解退，因此声明一个在构造和析构时会“喋喋不休”的类
 **/
class Demo {
    std::string word;
public:
    Demo(const std::string & str) {
        word = str;
        std::cout << "Demo " << word << " created.\n";
    };
    ~Demo() { // 鉴于此类不会被继承，因此析构函数可以不被声明为 virtual
        std::cout << "Demo " << word << " destroyed.\n";
    }
    void show() const {
        std::cout << "Demo " << word << " lives!\n";
    }
};

#endif // DEMO_H_