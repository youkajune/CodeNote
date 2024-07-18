#include "StringBad.h"
#include "String.h"
#include <iostream>

// 引用传递
void callStringBad1(StringBad &);
// 值传递
void callStringBad2(StringBad);
// StringBad 类的使用
void useStringBad();

// String 类的使用
void useString();

int main() {
//    useStringBad();
    useString();
    return 0;
}

void useStringBad() {
    using std::cout;
    using std::endl;
    cout << "Use StringBad.\n";
    StringBad sb1("Hello, World");
    StringBad sb2("You Ka");
    StringBad sb3("Mo Xu");
    cout << "sb1: " << sb1 << endl;
    cout << "sb2: " << sb2 << endl;
    cout << "sb3: " << sb3 << endl;
    callStringBad1(sb1);
    cout << "sb1: " << sb1 << endl;
    // 复制构造函数
    callStringBad2(sb2);
    cout << "sb2: " << sb2 << endl;
    cout << "Initialize one object to another:\n";
    // 复制构造函数
    StringBad sb4 = sb3;
    cout << "sb4: " << sb4 << endl;
    cout << "Assign one object to another:\n";
    // 赋值运算符
    StringBad sb5;
    sb5 = sb1;
    cout << "sb5: " << sb5 << endl;
    cout << "End of useStringBad().\n";
}

void callStringBad1(StringBad & sb) {
    std::cout << "Passed By Reference --- StringBad: \"" << sb << "\"\n";
}

void callStringBad2(StringBad sb) {
    std::cout << "Passed By Value --- StringBad: \"" << sb << "\"\n";
}
void useString() {
    using std::cout;
    using std::endl;
    const int SIZE = 10;
    const int CHAR_SIZE = 40;
    String arr[SIZE];

    for (int i = 0; i < SIZE; i++) {
        cout << "Please input " << SIZE - i << " words.\n";
        std::cin >> arr[i];
    }

    for (int j = 0; j < SIZE; j++) {
        cout << arr[j] << endl;
    }
}