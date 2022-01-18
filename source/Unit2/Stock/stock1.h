#ifndef STOCK1_H_
#define STOCK1_H_
#include <iostream>
/*
 * 类声明的完整练习 —— 包括构造函数和析构函数
 */
class Stock {
private:
    std::string company; // 公司
    long shares; // 持有的股数
    double share_value; // 股票实时单价
    double total_value; // 持有的股票总价
    void set_tot();
public:
    /**
     * 股票初始化
     */
    Stock(); // 默认构造方法，除此之外，还可以通过为已有构造方法的所有参数都提供默认值来创建默认构造方法
    Stock(const Stock &);
    Stock(const std::string& co, long num = 0, double val = 0.0);
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
    /**
     * 析构函数
     */
     ~Stock();
};
inline void Stock::set_tot() {
    total_value = share_value * shares;
}
#endif // STOCK1_H_