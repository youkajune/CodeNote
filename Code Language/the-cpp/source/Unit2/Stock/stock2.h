#ifndef STOCK2_H_
#define STOCK2_H_
#include <iostream>
class Stock {
private:
    std::string company; // 公司
    long shares; // 持有的股数
    double share_value; // 股票实时单价
    double total_value; // 持有的股票总价
    void set_tot() { total_value = share_value * shares; }

public:
    Stock();
    Stock(const Stock &);
    Stock(const std::string com, long num = 0, double price = 0.0);
    ~Stock();

    void buy(long num, double price);
    void sell(long num, double price);
    void update(double price);
    void show();
};
#endif // STOCK2_H_