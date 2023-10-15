#include <string>
#include <iostream>

/**
 * 测试 string 类的构造函数，ctor 是构造函数的缩写
 **/
void test_string_ctor() {
    using namespace std;
    string one("Hello World."); // ctor #1, 将 string 初始化为指针 s 指向的 NBTS
    cout << one << endl;

    string two(10, 'A'); // ctor #2, 将 string 初始化为包含 n 个字符 c 的字符串
    cout << two << endl;

    string three(one); // ctor #3 复制构造函数，将 string 初始化为另一个 string 对象
    cout << three << endl;

    one += " Opos!"; // 重载 += 运算符
    cout << one << endl;
    two = "Sorry! That was ";
    three[0] = 'P';

    string four; // ctor #4 默认构造函数
    four = two + three; // 重载 +, = 运算符
    cout << four << endl;

    char cString[] = "All's well that ends well";
    string five(cString, 10); // ctor #5
    cout << five << endl;

    string six(cString + 3, cString + 10); // ctor #6
    cout << six << ", ";
    
}

int main() {
    test_string_ctor();
    return 0;
}