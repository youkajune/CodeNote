#include "stock1.h"
Stock::Stock() {
    std::cout << "默认构造函数" << std::endl;
    company = "No Name";
    shares = 0;
    share_value = 0.0;
    set_tot();
}
Stock::Stock(const Stock & s) {
    std::cout << "这里是 Stock 复制构造函数" << std::endl;
    company = s.company;
    shares = s.shares;
    share_value = s.share_value;
    set_tot();
}
Stock::Stock(const std::string &co, long num, double val) {
    std::cout << "这里是 Stock(" + co + ", " << num << ", " << val << ")" << std::endl;

    company = co;
    if (num < 0) {
        std::cout << "购买数目不能为负，将 " + co + " 股票数目设置为 0." << std::endl;
        shares = 0;
    } else
        shares = num;
    share_value = val;
    set_tot();
}

void Stock::buy(long num, double price) {
    if (num < 0) {
        std::cout << "购买股票数目异常，购买失败" << std::endl;
        return;
    }
    shares += num;
    share_value = price;
    set_tot();
}

void Stock::sell(long num, double price) {
    if (num < 0) {
        std::cout << "出售股票数目异常，出售失败" << std::endl;
        return;
    }

    if (num > shares) {
        std::cout << "出售股票数目多于持有数目，出售失败" << std::endl;
        return;
    }

    shares -= num;
    share_value = price;
    set_tot();
}

void Stock::update(double price) {
    share_value = price;
    set_tot();
}

void Stock::show() {
    std::cout << "Company: " << company << std::endl
              << "Shares: " << shares << std::endl
              << "Share Price: $" << share_value << std::endl
              << "Total Worth: $" << total_value <<std::endl;
}

Stock::~Stock() {
    std::cout << "Stock 析构函数, Company: " << company << std::endl;
}