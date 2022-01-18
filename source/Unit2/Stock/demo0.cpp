#include "stock0.h"
/*
 * 类的简单使用:
 * Unit1. 声明类对象;
 * Unit2. 调用类的成员(公有成员,也称接口);
 */
int main(void) {
    // 声明两个 Stock 变量
    Stock sally;
    sally.show();
    Stock solly;
    sally.accquire("Coke", 3, 10.4);
    sally.show();
    sally.buy(-1, 5);
    sally.buy(3, 6);
    sally.show();
    sally.sell(-1, 3);
    sally.sell(3, 7);
    sally.show();
    sally.sell(7, 9);
    sally.show();

    return 0;
}