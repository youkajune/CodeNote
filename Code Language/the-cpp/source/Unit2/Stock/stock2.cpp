#include "stock2.h"
Stock::Stock() {
    std::cout << "This is Default Constructor Function.(默认构造函数)\n";
    company = "No Company";
    shares = 0;
    share_value = 0.0;
    set_tot();
    std::cout << "Default Constructor Function END." << std::endl;
}

Stock::Stock(const Stock & stock) {
    std::cout << "This is Copy Constructor Function.(复制构造函数)\n";
    company = stock.company;
    shares = stock.shares;
    share_value = stock.share_value;
    set_tot();
    std::cout << "Copy Constructor Function END." << std::endl;
}

Stock::Stock(const std::string com, long num, double price) {
    std::cout << "This is a Constructor Function —— Stock(const std::string, long, double)\n";
    company = com;
    if (num < 0) {
        std::cout << "Number is invalid. Number is set 0.\n";
        shares = 0;
    } else
        shares = num;
    share_value = price;
    set_tot();
    std::cout << "Constructor Function END." << std::endl;
}

Stock::~Stock() {
    std::cout << "Destructor Function. Company is " << company << std::endl << std::endl;
}

void Stock::buy(long num, double price) {
    if (num < 0) {
        std::cout << "Number is invalid.Buy Failed.\n";
        return;
    }
    shares += num;
    share_value = price;
    set_tot();
}

void Stock::sell(long num, double price) {
    if (num < 0) {
        std::cout << "Number is invalid. Sell Failed.\n";
        return;
    }
    if (num > shares) {
        std::cout << "Shares isn't enough. Sell Failed.\n";
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