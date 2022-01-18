#include "myfriend.h"
#include <iostream>
Time::Time() {
    std::cout << "Time Default Constructor. Address is " << this << std::endl;
    this->hours = 0;
    this->minutes = 0;
}

// this 指针的使用: 因为参数和成员变量的名称相同，因此需要使用 this 指针.
Time::Time(int hours, int minutes) {
    std::cout << "Time Constructor, hours = " << hours << " minutes = " << minutes << " address is " << this << std::endl;
    this->hours = hours;
    this->minutes = minutes;
}

Time::~Time() {
    std::cout << "Destructor. Address is " << this << std::endl;
}

Time Time::operator*(double n) const {
    Time res;
    long totalMinutes = (long) (n * (hours * 60 + minutes));
//    std::cout << totalMinutes << std::endl;
    res.hours = totalMinutes / 60;
    res.minutes = totalMinutes % 60;
//    std::cout << res.hours << " " << res.minutes << std::endl;
    return res;
}

// 友元版本的运算符重载
//Time operator*(double n, const Time & t) {
//    Time res;
//    long totalMinutes = (long) (n * (t.hours * 60 + t.minutes));
//    res.hours = totalMinutes / 60;
//    res.minutes = totalMinutes % 60;
//    return res;
//}

// 普通的非成员函数
Time operator*(double n, const Time & t) {
    return t * n;
}

void Time::show() const {
    std::cout << this->hours << " hours, " << this->minutes << " minutes. Address is " << this << std::endl;
}

std::ostream & operator<<(std::ostream & out, const Time & t) {
    std::cout << t.hours << " hours, " << t.minutes << " minutes. Address is " << &t << std::endl;
    return out;
}