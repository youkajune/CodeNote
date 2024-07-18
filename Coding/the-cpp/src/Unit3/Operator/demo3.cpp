#include "myfriend.h"
#include <iostream>
int main(void) {
    using std::cout;
    using std::endl;
    Time t1 = Time(4, 20);
    cout << "t1: " << endl;
    t1.show();
    cout << endl;

    Time t2;
    t2 = t1 * 1.5;
    cout << "t2: " << endl;
    t2.show();
    cout << endl;

    Time t3;
    t3 = 1.5 * t1;
    cout << "t3: " << endl;
    cout << t3 << endl;

    return 0;
}