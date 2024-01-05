#ifndef FORMAT_H
#define FORMAT_H

#include <iostream>

/**
 * 修改 IO 的整数进制
 **/
void test_count() {
    using namespace std;
    int n = 13;

    cout << "n    n*n\n";
    cout << n << "     " << n * n << " (decimal)" << endl;

    cout << hex; // 设置为十六进制显示整数
    cout << n << "     " << n * n << " (hexadecimal)" << endl;

    cout << oct << n << "     " << n * n << " (octal)" << endl; // 设置为八进制显示整数

    dec(cout); // 使用函数形式将其重置为十进制显示整数
    cout << n << "     " << n * n << " (decimal)" << endl;
}

/**
 * 修改输出的字段宽度
 **/
void test_width() {
    using namespace std;
    // 示例一
    cout << '#';
    cout.width(10);
    cout << 12 << '#' << 24 << "#\n";

    // 示例二
    int w = cout.width();
    cout << "Default field width = " << w << endl;
    cout.width(8);
    cout << "N" << ":";
    cout.width(10);
    cout << "N*N" << ":\n";
    for (int i = 1; i <= 100; i *= 10) {
        cout.width(8);
        cout << i << ":";
        cout.width(10);
        cout << i*i << ":\n";
    }
}

/**
 * 修改浮点数精度
 **/
void test_precision() {
    using std::cout;
    using std::endl;
    float f1 = 20.400;
    float f2 = 1.33 + 7.1 / 3.0;

    cout << "Default f1 = " << f1 << endl;
    cout << "Default f2 = " << f2 << endl;

    cout.precision(2);
    cout << "Changed f1 = " << f1 << endl;
    cout << "Changed f2 = " << f2 << endl;
}
#endif // FORMAT_H