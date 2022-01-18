#ifndef VECTOR_H_
#define VECTOR_H_
#include <iostream>
namespace VECTOR {
    class Vector {
    public:
        enum Mode {
            RECT, // 直角坐标系
            POL   // 极坐标系
        };
    private:
        double x; // 水平坐标
        double y; // 垂直坐标
        double ang; // 角度
        double mag; // 长度
        Mode mode; // 采用的坐标系
        // 设置私有成员的函数
        void setMag(); // 根据 x, y 设置 mag
        void setAng(); // 根据 x, y 设置 ang
        void setX(); // 根据 mag, ang 设置 x
        void setY(); // 根据 mag, ang 设置 y
    public:
        Vector();
        // 构造函数, 默认采用直角坐标系表示法
        Vector(double n1, double n2, Mode form = RECT);
        ~Vector();
        // 重置 Vector 值, 默认采用直角坐标系表示法
        void reset(double n1, double n2, Mode form = RECT);
        double getXVal() const { return x; }
        double getYVal() const { return y; }
        double getAngVal() const { return ang; }
        double getMagVal() const { return mag; }
        void setPolarMode();
        void setRectMode();
        // 重载运算符 —— 成员函数
        Vector operator+(const Vector & vec) const;
        Vector operator-(const Vector & vec) const;
        Vector operator-() const;
        Vector operator*(double d) const;
        // 重载运算符 —— 友元函数
        friend Vector operator*(double d, const Vector & vec);
        friend std::ostream & operator<<(std::ostream & out, const Vector & vec);
    };
} // end namespace VECTOR
#endif // VECTOR_H_