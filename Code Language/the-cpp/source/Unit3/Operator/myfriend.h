#ifndef MYFRIEND_H_
#define MYFRIEND_H_
#include <iostream>
class Time {
private:
    int hours;
    int minutes;
public:
    Time();
    Time(int, int);
    ~Time();
    void show() const;
    Time operator*(double n) const;
//    friend Time operator*(double n, const Time & t);
    // 重载 << 运算符
    friend std::ostream & operator<<(std::ostream & out, const Time &);
};
Time operator*(double n, const Time &);
#endif // MYFRIEND_H_