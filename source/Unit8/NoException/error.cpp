#include <iostream>
#include <cstdlib>
#include <cfloat>
#include <exception>

/**
 * 演示没有异常类时需要做的处理
 **/

// abort() 异常终止
double hmean1(double a, double b);
void test_abort();
// 返回错误码
bool hmean2(double a, double b, double & res);
void test_errorCode();
// 异常处理
double hmean3(double a, double b);
void test_Exception();

int main(void) {
//    test_abort();
//    test_errorCode();
    test_Exception();
    return 0;
}

double hmean1(double a, double b) {
    if (a == -b) {
        std::cout << "untenable arguments to hmean()\n";
        std::abort();
    }
    return 2.0 * a * b / (a+b);
}

void test_abort() {
    std::cout << "Abort test.\n";
    double x, y, z;
    std::cout << "Enter two numbers: ";
    while (std::cin >> x >> y) {
        z = hmean1(x, y);
        std::cout << "Harmonic mean of " << x << " and " << y << " is " << z << std::endl;

        std::cout << "Enter next set of numbers <q to quit>.";
    }
    std::cout << "Bye.\n";
}

bool hmean2(double a, double b, double & res) {
    if (a == -b) {
        res = DBL_MAX; // double 最大值
        return false;
    }
    res = 2.0 * a * b / (a+b);
    return true;
}

void test_errorCode() {
    std::cout << "ErrorCode test.\n";
    double x, y, z;
    std::cout << "Enter two numbers: ";
    while (std::cin >> x >> y) {
        if (hmean2(x, y, z)) {
            std::cout << "Harmonic mean of " << x << " and " << y << " is " << z << std::endl;
        } else {
            std::cout << "One value shouldn't be the negative of the other - try again.\n";
        }
        std::cout << "Enter next set of numbers <q to quit>.";
    }
    std::cout << "Bye.\n";
}

double hmean3(double a, double b) {
    if (a == -b) {
        throw "Invalid value: One value shouldn't be the negative of the other - try again."; // 发现异常情况，抛出异常
    }
    return 2.0 * a * b / (a+b);
}

void test_Exception() {
    double x, y, z;
    std::cout << "Enter two numbers: ";
    while (std::cin >> x >> y) {
        try {
            z = hmean3(x, y); // 尝试捕获异常
        } catch (const char * ptr) {
            // 异常被捕获，处理异常
            std::cout << ptr << std::endl << "Enter a new pair of numbers: " << std::endl;
            continue;
        }
        std::cout << "Harmonic mean of " << x << " and " << y << " is " << z << std::endl;
        std::cout << "Enter next set of numbers <q to quit>.";
    }
    std::cout << "Bye.\n";
}