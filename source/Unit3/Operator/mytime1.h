#ifndef MYTIME1_H_
#define MYTIME1_H_

class Time {
private:
    int hours;
    int minutes;
public:
    Time();
    Time(int hours, int minutes);
    ~Time();

    void show() const;
    void modify(int hours, int minutes);
    void addHours(int hours);
    void addMinutes(int minutes);
    Time sum(const Time & t) const;
};
#endif // MYTIME1_H_