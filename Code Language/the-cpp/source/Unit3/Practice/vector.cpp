#include "vector.h"
#include <cmath>
namespace VECTOR {
    using std::sqrt;
    using std::sin;
    using std::cos;
    using std::atan;
    using std::atan2;
    using std::cout;

    const double RadToDeg = 45.0 / atan(1.0); // 计算一弧度对应的角度

    /**
     * Private methods
     */
    void Vector::setAng() {
        // 这里其实不应该用 == 的, double 类型的 == 并不准确
        if (x == 0.0 && y == 0.0)
            ang = 0.0;
        else
            ang = atan2(y, x);
    }

    void Vector::setMag() {
        mag = sqrt(x * x + y * y);
    }

    void Vector::setX() {
        x = mag * cos(ang);
    }

    void Vector::setY() {
        y = mag * sin(ang);
    }

    /**
     * Public methods —— Constructor And Destructor
     */
    Vector::Vector() {
//        cout << "Default Constructor.\n";
        x = y = ang = mag = 0.0;
        mode = RECT;
    }

    Vector::Vector(double n1, double n2, Mode form) {
//        cout << "Constructor. ";
        mode = form;
        if (form == RECT) {
            x = n1;
            y = n2;
            setMag();
            setAng();
        } else if (form == POL) {
            mag = n1;
            ang = n2 / RadToDeg;
            setX();
            setY();
        } else {
            cout << "Constructor Vector()'s third argument is invalid. Object value will be set 0, mode = RECT.";
            x = y = ang = mag = 0.0;
            mode = RECT;
        }
//        cout << std::endl;
    }

    Vector::~Vector() {
//        cout << "Destructor.\n";
    }

    /**
     * Public Function.
     */
     // 重新设置 vector 的值
    void Vector::reset(double n1, double n2, Mode form) {
        mode = form;
        if (mode == RECT) {
            x = n1;
            y = n2;
            setAng();
            setMag();
        } else if (mode == POL) {
            mag = n1;
            ang = n2 /RadToDeg;
            setX();
            setY();
        } else {
            cout << "reset() 's third argument is invalid. Object value will be set 0, mode = RECT.\n";
            x = y = ang = mag = 0.0;
            mode = RECT;
        }
    }

    void Vector::setPolarMode() { mode = RECT; }

    void Vector::setRectMode() { mode = POL; }

    /**
     * Operator overload —— Member Function
     */
    Vector Vector::operator+(const Vector &vec) const {
        return Vector(x + vec.x, y + vec.y, RECT);
    }

    Vector Vector::operator-(const Vector &vec) const {
        return Vector(x - vec.x, y - vec.y, RECT);
    }

    Vector Vector::operator-() const {
        return Vector(-x, -y, RECT);
    }

    Vector Vector::operator*(double d) const {
        return Vector(x * d, y * d, RECT);
    }
    /**
     * Operator overload —— Friend Function
     */
    Vector operator*(double d, const Vector & vec) {
        return vec * d;
    }

    // 如果 mode 是 RECT, 显示直角坐标系的坐标;
    // 如果 mode 是 POL , 显示极坐标系的坐标.
    std::ostream & operator<<(std::ostream & out, const Vector & vec) {
        if (vec.mode == Vector::RECT) {
            out << "(x, y) = (" << vec.x << ", " << vec.y << ")";
        } else if (vec.mode == Vector::POL) {
            out << "(mag, ang) = (" << vec.mag << ", " << vec.ang * RadToDeg << ")";
        } else {
            out << "Vector object mode is invalid.";
        }
        return out;
    }
}