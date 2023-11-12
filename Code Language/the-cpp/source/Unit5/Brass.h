#ifndef BRASS_H_
#define BRASS_H_

#include <string>
#include <iostream>
class Brass {
private:
    std::string name; // 用户名
    long account; // 账号
    double balance; // 余额
public:
    Brass(const std::string & n = "Null", long ac = -1, double b = 0.0) : name(n), account(ac), balance(b) {};
    void deposit(double money); // 存款
    double getBalance() const { return balance; } // 获取余额
    virtual void withdrawal(double money); // 取款
    virtual void show() const;
    virtual ~Brass() { std::cout << "~Brass()\n"; }
};

class BrassPlus : public Brass {
private:
    double maxLoan; // 贷款上限
    double rate; // 利率
    double totalLoan; // 可贷款的总额
public:
    BrassPlus(const std::string & n = "Null", long ac = -2, double b = 0.0, double ml = 500, double r = 0.1125) : Brass(n, ac, b), maxLoan(ml), rate(r), totalLoan(0) {};
    BrassPlus(const Brass & b, double ml = 500, double r = 0.1125) : Brass(b), maxLoan(ml), rate(r), totalLoan(0) {};
    virtual void withdrawal(double money);
    virtual void show() const;
    void setMaxLoan(double m) { maxLoan = m; }
    void setRate(double r) { rate = r; }
    void setTotalLoad() { totalLoan = 0; }
    ~BrassPlus() { std::cout << "~BrassPlus().\n"; }
};

#endif // BRASS_H_