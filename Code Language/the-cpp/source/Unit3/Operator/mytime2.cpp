#include "mytime2.h"
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
Time::Time(const Time & t) {
    std::cout << "Copy Constructor. Address is " << this <<  std::endl;
    hours = t.hours;
    minutes = t.minutes;
}

Time::~Time() {
    std::cout << "Destructor. Address is " << this << std::endl;
}

void Time::addHour(int h) {
    this->hours = this->hours + h;
}

void Time::addMinute(int m) {
    this->minutes = this->minutes + m;
    if (this -> minutes > 60) {
        this->hours++;
        this->minutes %= 60;
    }
}

void Time::show() const {
    std::cout << this->hours << " hours, " << this->minutes << " minutes. Address is " << this << std::endl;
}

void Time::modify(int h, int m) {
    this->hours = h;
    this->minutes = m;
}

Time Time::operator+(const Time & t) const {
    Time sum;
    sum.minutes = this->minutes + t.minutes;
    sum.hours = this->hours + t.hours + sum.minutes / 60;
    sum.minutes %= 60;
    std::cout << "hours is " << sum.hours << ". minutes is " << sum.minutes << ". Sum's address is " << &sum << std::endl;
    return sum;
}