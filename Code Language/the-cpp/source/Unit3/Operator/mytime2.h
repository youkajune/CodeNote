#ifndef MYTIME2_H_
#define MYTIME2_H_

class Time {
private:
    int hours;
    int minutes;
public:
    Time();
    Time(int, int);
    Time(const Time &);
    ~Time();
    void addHour(int);
    void addMinute(int);
    void show() const;
    void modify(int, int);
    Time operator+(const Time &) const;
};
#endif // MYTIME2_H_
