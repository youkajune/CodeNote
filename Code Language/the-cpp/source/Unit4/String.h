//
// Created by MoZiYu on 2022/Unit3/31.
//

#ifndef SOURCE_STRING_H
#define SOURCE_STRING_H
#include <iostream>

class String {
private:
    char* str;
    int len;
    static int strNum;
public:
    // constructors and destructors
    String();
    String(char * p);
    String(const String &);
    ~String();

    // overload operator methods
    String & operator=(String &);
    String & operator=(const char *);
    char & operator[](int index);
    const char & operator[](int index) const;

    // overload operators friends
    friend bool operator<(const String & s1, const String & s2);
    friend bool operator>(const String & s1, const String & s2);
    friend bool operator==(const String & s1, const String & s2);
    friend std::ostream & operator<<(std::ostream &, const String &);
    friend std::istream & operator>>(std::istream & in, String & s);

    // member function
    int length() const { return len; };
    // static member function
    static int HowMany();
};

#endif //SOURCE_STRING_H
