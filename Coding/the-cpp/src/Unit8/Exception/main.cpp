#include "Exception.h"
#include <cmath>
// 调和平均数
double hmean(double x, double y) {
    if (x == -y)
        throw HmeanException(x, y);
    return 2.0 * x * y / ( x + y );
}

// 几何平均数
double gmean(double x, double y) {
    if (x < 0 || y < 0)
        throw GmeanException(x, y);
    return std::sqrt( x * y );
}

/**
 * 测试自定义异常类
 **/
void test_mean() {
    double x, y, z;

    while (std::cin >> x >> y) {
        try {
            z = hmean(x, y);
            std::cout << "Harmonic mean of " << x << " and " << y << " is " << z << std::endl;
            z = gmean(x, y);
            std::cout << "Geometric mean of " << x << " and" << y << " is " << z << std::endl;
        } catch (HmeanException & e) {
            std::cout << e.getMessage() << std::endl;
            continue;
        } catch (GmeanException & e) {
            std::cout << e.getMessage() << std::endl;
            break; // 和 hmean 异常采用不同的语句
        } catch (...) {
            std::cout << "Unknown Exception" << std::endl;
            continue;
        }
        std::cout << "Enter next set of numbers <q to quit>.";
    }
}

/**
 * 自定义异常类
 **/
class MyException : public std::exception {
private:
    std::string Msg;
public:
    // 必须显式调用的构造函数
    explicit MyException(const char * p) : Msg(p) { std::cout << "创建一个 MyException 对象: " << Msg << std::endl; }
    // 必须显示调用的构造函数
    explicit MyException(const std::string & str) : Msg(str) { std::cout << "创建一个 MyException 对象: " << Msg << std::endl; }
    // 复制构造函数,以便可以在 catch 块捕获异常时能够打印信息
    MyException(const MyException & ME) : Msg(ME.Msg) { std::cout << "复制构造函数, Msg: " << Msg << std::endl; }
    // 赋值运算符
    MyException& operator= (MyException & me) {
        Msg = me.Msg;
        std::cout << "赋值运算符, Msg: " << Msg << std::endl;
        return *this;
    }
    virtual ~MyException() noexcept { std::cout << "销毁 Msg: " << Msg << " 的 MyException 对象" << std::endl; } // 析构函数被声明为虚函数, 不抛出异常
    // 重写基类的 public 方法
    const char * what() const _GLIBCXX_TXN_SAFE_DYN _GLIBCXX_NOTHROW override {
        return Msg.c_str();
    }
};
/**
 * 一个可能抛出 MyException 异常的函数
 **/
void func() {
//    MyException me("MyException error");
//    throw me;
    throw MyException("MyException error");
}

/**
 * 测试异常的其他特性：
 *     - 与函数返回机制相似，但有差别
 *     - 引发异常时编译器总是创建一个临时变了，即使 try...catch 的 catch 块中捕获的异常是引用
 **/
void test_characteristics() {
    try {
        func();
    } catch (MyException & err) {
        std::cout << "Error Msg: " << err.what() << std::endl;
    }
}

/**
 * 关于动态内存分配和异常能协同工作的演示
 **/
void test_dynamic_1() {
    bool badThingHappened = true;

    std::string str("HelloWorld.");
    if (badThingHappened) {
        throw std::exception();
    }
//    return;
}

/**
 * 关于动态内存分配和异常不能协同工作的演示
 * */
void test_dynamic_2(int n) {
    bool badThingHappened = true;

    int * p = new int[n];
    if (badThingHappened) {
        throw std::exception();
    }

    delete [] p;
//    return;
}

/**
 * 关于动态内存分配和异常不能协同工作的演示
 * */
void test_dynamic_3(int n) {
    bool badThingHappened = true;

    int * p = new int[n];
    try {
        if (badThingHappened) {
            throw std::exception();
        }
    } catch (std::exception & e) {
        delete [] p;
        throw; // 将捕获的异常重新抛出，在这里相当于 throw std::exception();
    }
    delete [] p;
//    return;
}

int main() {
//    test_mean();
    test_characteristics();
    return 0;
}

