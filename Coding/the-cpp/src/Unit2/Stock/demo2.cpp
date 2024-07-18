/*
 * 构造函数和析构函数的练习
 * 这里主要演示 构造函数和析构函数被调用的时机
 */
#include "stock2.h"

Stock s1 = Stock("Stock1", 30, 55.5);
static Stock s2 = Stock("Stock2", 40, 40.3);
int main() {
    using std::cout;
    using std::endl;

    cout << endl << "Show s1 Information: " << endl;
    s1.show();
    cout << endl << "Show s2 Information: " << endl;
    s2.show();
    {
        cout << endl << "Create s3: " << endl;
        Stock s3 = Stock("Stock Unit3", 20, 10.4);
        cout << "Show s3 Information: " << endl;
        s3.show();
        cout << endl << "Create s4: " << endl;
        static Stock s4 = Stock("Stock Unit4", 30, 20.4);
        cout << "Show s4 Information: " << endl;
        s4.show();
        cout << endl << "Create s5: " << endl;
        Stock s5 = s1;
        cout << "Show s5 Information: " << endl;
        s5.show();
        cout << "Assign s2 to s5: " << endl;
        s5 = s2;
        cout << "Show s5 Information: " << endl;
        s5.show();
        cout << "Assign s5: " << endl;
        s5 = Stock("Stock Unit5", 23, 6);
        cout << "Show s5 Information: " << endl;
        s5.show();
        cout << endl << "Create s6:" << endl;
        Stock s6 = {"Stock Unit6", 32, 4.9};
    }
    cout << "Main END.\n";
    return 0;
}