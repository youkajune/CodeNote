#include "Brass.h"
#include <iostream>
// Brass Methods
void Brass::deposit(double money) { // 存款
    if(money < 0) {
        std::cout << "Failed. Negative deposit not allowed." << std::endl;
        return;
    }
    balance += money;
    std::cout << "Success. " << name << " deposits $" << money << ".\n";
}

void Brass::withdrawal(double money) { // 取款
    if (money < 0)
        std::cout << "Failed. Negative withdrawal not allowed." << std::endl;
    else if (money > balance)
        std::cout << "Failed. Withdrawal amount of $" << money << " exceeds your balance($"<< balance <<").\n";
    else {
        balance -= money;
        std::cout << "Success. " << name << " Withdrawal $" << money << ", Left $" << balance << ".\n";
    }
}

void Brass::show() const {
    std::cout << "Account: " << account << std::endl;
    std::cout << "UserName: " << name << std::endl;
    std::cout << "Balance: " << balance << std::endl;
}

// BrassPlus Methods
void BrassPlus::withdrawal(double money) { // 取款
    double balance = getBalance();
    if (money <= balance) {
        Brass::withdrawal(money);
    } else if (money > balance + maxLoan - totalLoan) { // 取款大于(存款 + 剩余可贷款额度)
        std::cout << "Failed. Withdrawal $" << money << " exceeds upper limit.\n";
    } else {
        // 先向银行借款
        deposit(money - balance);
        // 算上利息共需要还银行的钱
        totalLoan += balance * (1.0 + rate);
        // 然后再取款
        Brass::withdrawal(money);
    }
}

void BrassPlus::show() const {
    Brass::show();
    std::cout << "Max Loan: " << maxLoan << std::endl;
    std::cout << "Total Loan: " << totalLoan << std::endl;
    std::cout << "Rate: " << rate << std::endl;
}