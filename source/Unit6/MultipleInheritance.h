#ifndef MULTIPLEINHERITANCE_H_
#define MULTIPLEINHERITANCE_H_

#include <iostream>

/*
 * 练习多重继承
 */
class Worker {
private:
    std::string name; // 名字
    long id; // identify
    // ---- modify ----
protected:
    virtual void output() const;
    virtual void input();
    // ---- ------ ----
public:
    Worker() : name("no name"), id(0) {} // default constructor
    Worker(const std::string &s, long n) : name(s), id(n) {} // constructor
    virtual ~Worker() = 0; // destructor and pure virtual
    virtual void set() = 0;
    virtual void show() const = 0;
};

class Waiter : virtual public Worker { // 为了避免多重继承包含多个Worker子对象而引入虚基类
private:
    int panache;
    // ---- modify ----
protected:
    virtual void output() const; // 只显示Waiter组件的数据成员 —— panache
    virtual void input(); // 只输入Waiter组件的数据成员
    // ---- ------ ----
public:
    Waiter() : Worker(), panache(0) {}
    Waiter(const Worker &wk, int p = 0) : Worker(wk), panache(p) {}
    Waiter(const std::string &s, long n, int p = 0) : Worker(s, n), panache(p) {}
    virtual void set();
    virtual void show() const;
};

class Singer : virtual public Worker {
public:
    // 其他，女中音，女中音，女高音，男低音，男中音，男高音
    enum { OTHER, ALTO, CONTRALTO, SOPRANO, BASS, BARITONE, TENOR };
    enum { VTYPES = 7 };
private:
    static const char * pv[VTYPES]; // 记录声音类型的字符串
    int voice;
    // ---- Modify ----
protected:
    virtual void output() const;
    virtual void input();
    // ---- ------ ----
public:
    Singer() : Worker(), voice(OTHER) {}
    Singer(const Worker & wk, int v = OTHER) : Worker(wk), voice(v) {}
    Singer(const std::string & s, long n, int v = OTHER) : Worker(s, n), voice(v) {}
    virtual void set();
    virtual void show() const;
};

class SingingWaiter : public Singer, public Waiter {
// ---- Modify ----
protected:
    virtual void output() const;
    virtual void input();
    // ---- ------ ----
public:
    SingingWaiter() {} // 自动调用基类默认构造函数
    SingingWaiter(const std::string & s, long n, int p = 0, int v = Singer::OTHER)
            : Worker(s, n), Waiter(s, n, p), Singer(s, n, v) {}
    SingingWaiter(const Worker & wk, int p = 0, int v = Singer::OTHER)
            : Worker(wk), Waiter(wk, p), Singer(wk, v) {}
    SingingWaiter(const Waiter & wt, int v = Singer::OTHER)
            : Worker(wt), Waiter(wt), Singer(wt, v) {}
    SingingWaiter(const Singer & sg, int p = 0)
            :Worker(sg), Waiter(sg, p), Singer(sg) {}
    void set();
    void show() const;
};

// Worker methods implement
Worker::~Worker() {} // 必须提供析构函数的定义，哪怕是纯虚析构函数

void Worker::input() {
    std::cout << "Please input name: ";
    std::getline(std::cin, name);
    std::cout << "Please input worker's ID: ";
    std::cin >> id;
}

void Worker::output() const {
    std::cout << "Name: " << name << std::endl;
    std::cout << "ID  : " << id << std::endl;
}

// Waiter methods implement
void Waiter::output() const {
    std::cout << "Panache: " << panache << std::endl;
}

void Waiter::input() {
    std::cout << "Please input waiter's panache rating: ";
    std::cin >> panache;
}

void Waiter::set() {
    Worker::input();
    input();
    while (std::cin.get() != '\n')
        continue;
}

void Waiter::show() const {
    std::cout << "Category: waiter.\n";
    Worker::output();
    Waiter::output();
}

// Singer methods implement
const char * Singer::pv[] = {"other", "alto", "contralto",
                             "soprano", "base", "baritone", "tenor" };

void Singer::input() {
    std::cout << "Please input voice type: \n";
    // 展示选项
    int i = 0;
    while (i < VTYPES) {
        std::cout << i << ": " << pv[i] << "  ";
        if (i % 4 == 3)
            std::cout << std::endl;
        i++;
    }
    if (i % 4 != 0)
        std::cout << std::endl;
    // 输入选项
    while (std::cin >> voice && (voice < 0 || voice >= VTYPES))
        std::cout << "Please input a value >= 0 and < " << VTYPES << std::endl;
}

void Singer::output() const {
    std::cout << "Vocal range: " << pv[voice] << std::endl;
}

void Singer::set() {
    Worker::input();
    input();
    // 处理多余字符
    while (std::cin.get() != '\n')
        continue;
}

void Singer::show() const {
    std::cout << "Category: singer.\n";
    Worker::output();
    Singer::output();
}

// SingingWaiter methods implements
void SingingWaiter::output() const {
    Waiter::output();
    Singer::output();
}

void SingingWaiter::input() {
    Waiter::input();
    Singer::input();
}

void SingingWaiter::set() {
    Worker::input();
    input();
    while (std::cin.get() != '\n')
        continue;
}

void SingingWaiter::show() const {
    std::cout << "Category: singer waiter.\n";
    Worker::output();
    output();
}
#endif // MULTIPLEINHERITANCE_H_