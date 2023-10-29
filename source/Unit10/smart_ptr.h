/**
 * 用于演示三种智能指针使用的 Report 类的头文件
 **/

#ifndef SMART_PTR_H
#define SMART_PTR_H

#include <string>
#include <iostream>

class Report {
private:
    std::string str;
public:
    Report(const std::string s) : str(s) {
        std::cout << "Report object created!\n";
    }

    virtual ~Report() {
        std::cout << "Report object deleted!\n";
    }

    void comment() const {
        std::cout << str << std::endl;
    }
};

#endif // SMART_PTR_H
