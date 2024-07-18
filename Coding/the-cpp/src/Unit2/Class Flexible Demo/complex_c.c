// C 语法的自定义类型
#include <stdio.h>
#include <stdlib.h>
// 自定义复数类型
typedef struct Complex {
    double real;
    double imag;
} Complex;

Complex add(const Complex * c1, const Complex * c2) {
    Complex tmp;
    tmp.real = c1->real + c2->real;
    tmp.imag = c1->imag + c2->imag;
    return tmp;
}

int main () {
    Complex c1 = {10.4, 4.3};
    Complex c2 = {13.2, 54.2};
    Complex c = add(&c1, &c2); // Complex 加法操作
    printf("Complex: %lf, %lf\n", c.real, c.imag);
    return 0;
}