/*
 * 重载运算符练习题：声明一个输出类，模仿 ostream 类的功能输出基本数据类型
 */
#ifndef OUTPUT_H_
#define OUTPUT_H_
#include <stdio.h>
enum class Output_Format {
    endl
};
class Output {
private:

public:
    Output & operator<<(int);
    Output & operator<<(double);
    Output & operator<<(char);
    Output & operator<<(Output_Format);
};

#endif // OUTPUT_H_