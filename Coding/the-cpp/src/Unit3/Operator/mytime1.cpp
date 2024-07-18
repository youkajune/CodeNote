#include "mytime1.h"
#include <iostream>
Time::Time() {
    std::cout << "Default Constructor." << std::endl;
    this->hours = this->minutes = 0;
}

Time::Time(int hours, int minutes) {
    this->hours = hours;
    this->minutes = minutes;
}

Time::~Time() {
    std::cout << "Destructor." << std::endl;
}

void Time::addHours(int h) {
    this->hours = this->hours + h;
}

void Time::addMinutes(int m) {
    this->minutes = this->minutes + m;
    if (this -> minutes > 60) {
        this->hours++;
        this->minutes %= 60;
    }
}

void Time::show() const {
    std::cout << this->hours << " hours, " << this->minutes << " minutes." << std::endl;
}

void Time::modify(int h, int m) {
    this->hours = h;
    this->minutes = m;
}

Time Time::sum(const Time &t) const {
    Time tmp;
    tmp.minutes = t.minutes + minutes;
    tmp.hours = t.hours + hours + tmp.minutes / 60;
    tmp.minutes %= 60;
    return tmp;
}