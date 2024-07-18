// C++ 语法的
#include <iostream>
class Complex {
private:
    double real;
    double imag;
public:
    Complex();
    Complex(double, double);
    Complex operator+(Complex &) const;
    void show();
};

Complex::Complex() {
    real = 0;
    imag = 0;
}

Complex::Complex(double real, double imag) {
    this->real = real;
    this->imag = imag;
}
Complex Complex::operator+(Complex& complex) const {
    Complex sum;
    sum.real = this->real + complex.real;
    sum.imag = this->imag + complex.imag;
    return sum;
}

void Complex::show() {
    std::cout << "C Plus Plus Complex: " << real << ", " << imag << std::endl;
}

int main() {
    Complex c1 = Complex(10.4, 4.3);
    Complex c2 = Complex(13.2, 54.2);
    Complex tmp = c1 + c2; // Complex 加法操作
    tmp.show();
    return 0;
}