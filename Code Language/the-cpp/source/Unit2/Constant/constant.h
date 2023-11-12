#ifndef CONSTANT_H_
#define CONSTANT_H_
// 类中的常量
class Demo1 {
public:
    enum {LENGTH = 30};
    int arr[LENGTH];
};

class Demo2 {
public:
    static const int LENGTH = 30;
    int arr[LENGTH];
};
#endif //CONSTANT_H_
