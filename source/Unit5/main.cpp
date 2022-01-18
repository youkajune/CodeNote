#include "person.h"
#include "Brass.h"
// Person和Student这对继承类的使用
void usePersonAndStudent() {
    using std::cout;
    using std::endl;
    Person p1 = Person("YouKa", 20220506);
    p1.doSomeThings();
    p1.walk();

    Student s1 = Student("MoZi", 20220507, "Computer", 202264);
    // 派生类调用基类方法
    s1.doSomeThings();
    s1.walk();
    // 派生类调用新增的成员函数
    s1.study();

    Student s2 = Student(p1, "Music", 202265);
    s2.doSomeThings();
    s2.walk();
    s2.study();
}
// Brass和BrassPlus这对继承类的使用
void useBrass() {
    using std::cout;
    using std::endl;

    Brass b1("Peppa", 220614, 4000.0);
    BrassPlus bp1("George", 220615, 2000.0);
    b1.show();
    cout << endl;
    bp1.show();
    cout << endl;

    // 指向派生类对象的基类指针
    Brass * p_b1 = &bp1;
    p_b1->show(); // 虽然p_b1是基类指针, 但这里会调用派生类的show(), 而不是基类的show()
    cout << endl;

    b1.withdrawal(4200);
    b1.withdrawal(2000);

    bp1.withdrawal(1000);
    bp1.withdrawal(1100);
    bp1.withdrawal(600);

    b1.show();
    cout << endl;
    bp1.show();
    cout << endl;

    // 解释为什么基类析构函数需要是虚函数
    // 如果声明为虚函数, 这里将指调用基类的析构函数, 不会调用派生类的析构函数
    Brass * p_b2 = new BrassPlus("YouKa", 220616, 2000.0);
    delete p_b2;
    cout << endl;
}
// 多态演示之引用
void useReference(Brass & rb) {
    rb.show();
}
// 多态演示之指针
void usePointer(Brass * pb) {
    pb->show();
}
// 非多态——赋值
void useObject(Brass ob) {
    ob.show();
}
// 多态演示
void polymorph() {
    Brass b("You Ka Brass", 220621, 10000);
    BrassPlus bp("You Ka BrassPlus", 220622, 12345);
    useReference(b);
    useReference(bp);
    std::cout << std::endl;
    usePointer(&b);
    usePointer(&bp);
    std::cout << std::endl;
    useObject(b);
    useObject(bp);
    std::cout << std::endl;
}
int main() {
//    usePersonAndStudent();
//    useBrass();
    polymorph();
    return 0;
}