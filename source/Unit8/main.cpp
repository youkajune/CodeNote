#include "Exception/Exception.h"
#include "iostream"

class Demo {
    int val;
public:
    Demo(int v = 0) : val(v) {}
    void show() { std::cout << "Demo val is " << val << std::endl; }
};

Demo * getObject(int v) {
    if (v == 2)
        return nullptr;
    return new Demo();
}

int main() {
    Demo * d1 = getObject(1);
    d1->show();
    Demo * d2 = getObject(2);
    d2->show();
    return 0;
}