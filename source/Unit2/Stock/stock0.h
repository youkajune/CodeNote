// source/Unit2.Unit1/stock0.h
#ifndef STOCK0_H_
#define STOCK0_H_
/*
 * 关于声明类和实现类成员函数的练习 —— 不包括构造函数和析构函数
 */
#include <iostream>

class Stock {
private:
    std::string company; // 公司
    long shares; // 持有的股数
    double share_value; // 股票实时单价
    double total_value; // 持有的股票总价
    // 设置 total_value 的值
//    void set_tot() {
//        total_value = shares * share_value;
//    } // 内联函数
    void set_tot();
public:
    /**
     * 股票初始化
     */
    void accquire(const std::string& co, long n, double pr);
    /**
     * 购买股票
     */
    void buy(long num, double price);
    /**
     * 出售股票
     */
    void sell(long num, double price);
    /**
     * 更新股票价格
     */
    void update(double price);
    /**
     * 展示股票信息
     */
    void show();
}; // 注意类声明以分号结尾

inline void Stock::set_tot() {
    total_value = shares * share_value;
}

#endif // STOCK0_H_