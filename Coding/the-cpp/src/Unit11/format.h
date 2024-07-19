#ifndef FORMAT_H
#define FORMAT_H

#include <iostream>

/**
 * �޸� IO ����������
 **/
void test_count() {
    using namespace std;
    int n = 13;

    cout << "n    n*n\n";
    cout << n << "     " << n * n << " (decimal)" << endl;

    cout << hex; // ����Ϊʮ��������ʾ����
    cout << n << "     " << n * n << " (hexadecimal)" << endl;

    cout << oct << n << "     " << n * n << " (octal)" << endl; // ����Ϊ�˽�����ʾ����

    dec(cout); // ʹ�ú�����ʽ��������Ϊʮ������ʾ����
    cout << n << "     " << n * n << " (decimal)" << endl;
}

/**
 * �޸�������ֶο��
 **/
void test_width() {
    using namespace std;
    // ʾ��һ
    cout << '#';
    cout.width(10);
    cout << 12 << '#' << 24 << "#\n";

    // ʾ����
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
 * �޸ĸ���������
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