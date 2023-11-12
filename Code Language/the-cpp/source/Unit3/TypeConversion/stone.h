#ifndef STONE_H_
#define STONE_H_
#include <iostream>
class Demo {
private:
    double value;
public:
    Demo(double p) { value = p; };
    double getValue() { return value; }
};

class Stone {
private:
    static const int LBS_PER_STN = 14; // Unit1 英石 = 14 磅
    int stone; // 英石
    double pds_left; // 剩余的磅数
    double pounds; // 磅
public:
    Stone();
    explicit Stone(double p);
    Stone(int s, double pl);
    Stone(Demo & d) { pounds = d.getValue(); };
    ~Stone();
    // 以磅的形式展示数据
    void show_stn() const;
    // 以英石和磅的形式展示数据
    void show_lbs() const;
    explicit operator double() const;
    operator Demo() const {return Demo(pounds);}
    inline int show(int v);
};
int Stone::show(int v) {
    return v;
}
#endif // STONE_H_