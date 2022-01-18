#ifndef STRINGBAD_H_
#define STRINGBAD_H_
#include <iostream>
class StringBad {
private:
    char* str; // 字符指针
    int len; // 记录字符串长度
    static int strNum; // 记录StringBad对象数目
//    static const double s;
public:
    StringBad();
    StringBad(const char *);
    StringBad(const StringBad &);
    ~StringBad();
    StringBad & operator=(const StringBad &);
    friend std::ostream & operator<<(std::ostream &, const StringBad &);
};
#endif // STRINGBAD_H_