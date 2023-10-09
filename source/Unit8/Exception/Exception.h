#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include <iostream>

/**
 * 用于 hmean() 的自定义异常类
 **/
class HmeanException {
private:
    std::string errMessage; // 错误信息
    double v1; // 用于计算的值1
    double v2; // 用于计算的值2
public:
    HmeanException(double a, double b); // constructor
    std::string & getMessage() { return errMessage; } // 获取异常信息
};

HmeanException::HmeanException(double a, double b) : v1(a), v2(b) {
    errMessage = "Hmean(" + std::to_string(a) + ", " + std::to_string(b) + "). Invalid value: a = -b.";
}

/**
 * 用于 gmean() 的自定义异常
 **/
class GmeanException {
private:
    std::string errMessage;
    double v1;
    double v2;
public:
    GmeanException(double x, double y);
    std::string & getMessage() { return errMessage; }
};

GmeanException::GmeanException(double x, double y) : v1(x), v2(y) {
    errMessage = "Gmean(" + std::to_string(x) + ", " + std::to_string(y) + ") argument should be >=0.";
}
#endif // EXCEPTION_H_