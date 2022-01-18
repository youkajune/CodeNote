#include "stock0.h"

void Stock::accquire(const std::string &co, long n, double pr) {
    company = co;
    if (n < 0) {
        std::cout << "购买股票的数目无效，" << company << " 公司股票数目设置为 0.\n";
        shares = 0;
    }
    else {
        shares = n;
    }
    share_value = pr;
    // 更新 total_value
    set_tot();
}

void Stock::buy(long num, double price) {
    if (num < 0) {
        std::cout << "购买 " << company << " 公司股票数目异常,购买无效\n";
        return;
    }
    shares += num;
    share_value = price;
    set_tot();
}

void Stock::sell(long num, double price) {
    if (num < 0) {
        std::cout << "出售 " << company << " 公司股票数目异常，出售无效\n";
    } else if (num > shares) {
        std::cout << "出售数目多于持有数目\n";
    } else {
        shares -= num;
        share_value = price;
        set_tot();
    }
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
