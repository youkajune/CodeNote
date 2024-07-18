#ifndef CLASSTEMPLATE_H_
#define CLASSTEMPLATE_H_
#include <iostream>

/**
 * 最基本的类模板示例 —— 固定大小的栈模板
 **/
template<typename Type>
class StackV1 {
private:
    enum {MAX = 10}; // 默认栈大小
    Type items[MAX];
    int top;
public:
    StackV1();
    bool isEmpty() const;
    bool isFull() const;
    bool pop(Type & t);
    bool push(const Type & t);
};

// StackV1 template implement start
template<typename Type>
StackV1<Type>::StackV1() {
    top = 0;
}

template<typename Type>
bool StackV1<Type>::isEmpty() const {
    return top == 0;
}

template<typename Type>
bool StackV1<Type>::isFull() const {
    return top == MAX;
}

template<typename Type>
bool StackV1<Type>::push(const Type & t) {
    if (top >= MAX)
        return false;
    items[top++] = t;
    return true;
}

template<typename T>
bool StackV1<T>::pop(T &t) {
    if (top <= 0)
        return false;
    t = items[--top];
    return true;
}
// StackV1 template implement end

/**
 * 栈模板进阶版 —— 可动态调整大小的栈模板
 **/
template<typename Type>
class StackV2 {
private:
    enum {MAX = 10};
    int size;
    Type * items;
    int top;
public:
    explicit StackV2(int s = MAX);
    StackV2(const StackV2 & s);
    StackV2 & operator=(const StackV2 & s);
    ~StackV2();
    bool isEmpty() const;
    bool isFull() const;
    bool push(const Type & t); // 入栈
    bool pop(Type & t); // 出栈
};

// StackV2 template implement start
template<typename Type>
StackV2<Type>::StackV2(int s) : size(s), top(0) {
    items = new Type[s];
}

template<typename Type>
StackV2<Type>::StackV2(const StackV2 & s) : size(s.size), top(s.top){
    items = new Type [size];
    for (int i = 0; i < top; ++i) {
        items[i] = s.items[i];
    }
}

template<typename Type>
StackV2<Type> & StackV2<Type>::operator=(const StackV2<Type> & s) {
    if (this == &s)
        return *this;

    delete [] items;

    size = s.size;
    items = new Type [size];
    for (int i = 0; i < top; ++i) {
        items[i] = s.items[i];
    }
    top = s.top;
    return *this;
}

template<typename Type>
StackV2<Type>::~StackV2() {
    delete[] items;
}

template<typename Type>
bool StackV2<Type>::isEmpty() const {
    return top == 0;
}

template<typename Type>
bool StackV2<Type>::isFull() const {
    return top == size;
}

template<typename Type>
bool StackV2<Type>::push(const Type & t) {
    if (top >= size)
        return false;

    items[top++] = t;
    return true;
}

template<typename Type>
bool StackV2<Type>::pop(Type & t) {
    if (top <= 0)
        return false;

    t = items[--top];
    return true;
}
// StackV2 template implement end

/**
 * 带有非类型参数的模板类 —— Array 数组容器模板类
 **/
template<typename Type, int n>
class Array {
private:
    Type arr[n];
public:
    Array() {};
    explicit Array(const Type & t); // 转换函数，将所有元素初始化为t
    virtual Type & operator[](int i);
    virtual Type operator[](int i) const;
};

// Array template implement start
template<typename Type, int n>
Array<Type, n>::Array(const Type & t) {
    for (int i = 0; i < n; ++i) {
        arr[i] = t;
    }
}

template<typename Type, int n>
Type & Array<Type, n>::operator[](int i) {
    if (i < 0 || i >= n) {
        std::cout << "Array index is out of range.\n";
        std::exit(EXIT_FAILURE);
    }

    return arr[i];
}

template<typename Type, int n>
Type Array<Type, n>::operator[](int i) const {
    if (i < 0 || i >= n) {
        std::cout << "Array index is out of range.\n";
        std::exit(EXIT_FAILURE);
    }
    return arr[i];
}
// Array template implement end

/**
 * 使用多个类型参数的模板 —— 实现 Pair 模板类
 **/
template <typename T1, typename T2>
class Pair {
private:
    T1 t1;
    T2 t2;
public:
    Pair() {}
    Pair(const T1 & val1, const T2 & val2) : t1(val1), t2(val2) {}
    T1 & first();
    T1 first() const { return t1; }
    T2 & second();
    T2 second() const { return t2; }
};

// Pair template implement start
template<typename T1, typename T2>
T1 & Pair<T1, T2>::first() {
    return t1;
}

template<typename T1, typename T2>
T2 & Pair<T1, T2>::second() {
    return t2;
}
// Pair template implement end

/**
 * 模板类的成员也是模板 —— 模板的嵌套
 **/
template <typename T>
class MemberTemplate {
private:
    // 成员模板类
    template<typename V>
    class MemberClass;
    MemberClass<T> mc_T; // 模板类实例化对象
    MemberClass<int> mc_int; // 模板类实例化对象
public:
    MemberTemplate(T t, int i) : mc_T(t), mc_int(i) {} // constructor
    // 模板成员函数
    template<typename U>
    U memberFunc(U u, T t);
    void show() const { mc_T.show(); mc_int.show(); }
};

// MemberTemplate template implement start
template<typename T>
template<typename V>
class MemberTemplate<T>::MemberClass {
private:
    V val;
public:
    MemberClass(V v = 0) : val(v) {} // constructor
    void show() const { std::cout << val << std::endl; }
    V getValue() const { return val; }
};

template<typename T>
template<typename U>
U MemberTemplate<T>::memberFunc(U u, T t) {
    return (mc_T.getValue() + mc_int.getValue()) * u / t;
}
// MemberTemplate template implement end

/**
* 类模板的参数是另一个类模板
**/
template <template <typename T> class Type>
class Crab {
private:
    Type<int> s1;
    Type<double> s2;
public:
    Crab() {};
    bool push(int a, double x) { return s1.push(a) && s2.push(x); }
    bool pop(int & a, double & x) { return s1.pop(a) && s2.pop(x); }
};

/**
* 模板类中的普通友元函数(非模板友元)
**/
template <typename T>
class Friend1 {
private:
    static int cnt;
    T item;
public:
    Friend1(const T & i) : item(i) { cnt++; }
    ~Friend1() { cnt--; }
    friend void counts();
    friend void reports(Friend1<T> & rf);
};

// Friend1 template implement start
template <typename T>
int Friend1<T>::cnt = 0; // 静态数据成员的初始化

void counts() {
    std::cout << "int count: " << Friend1<int>::cnt << "; ";
    std::cout << "double count: " << Friend1<double>::cnt << std::endl;
}

// Friend<int> 的 reports()
void reports(Friend1<int> & rf) {
    std::cout << "Friend1<int>: " << rf.item << std::endl;
}

// Friend<double> 的 reports()
void reports(Friend1<double> & rf) {
    std::cout << "Friend1<double>: " << rf.item << std::endl;
}
// Friend1 template implement end

/**
 * 模板类中的约束友元函数
 **/
// Step Unit1. 声明友元函数的模板
template<typename T>
void count();

template<typename T>
void report(T & t);

// Step Unit2. 声明类模板
template<typename Type>
class Friend2 {
private:
    static int ct;
    Type item;
public:
    Friend2(const Type & t) : item(t) { ct++; }
    ~Friend2() { ct--; }
    friend void count<Type>(); // 模板函数实例化
    friend void report<>(Friend2<Type> & t);
};

template<typename Type>
int Friend2<Type>::ct = 0;

// Step Unit3. 友元模板函数的定义
template<typename Type>
void count() {
    std::cout << "template count: " << Friend2<Type>::ct << std::endl;
}

template<typename Type>
void report(Type & t) {
    std::cout << t.item << std::endl;
}

/**
 * 类模板中的非约束友元
 **/
template<typename T>
class Friend3 {
private:
    T item;
    static int cnt;
public:
    Friend3(const T & t) : item(t) { cnt++; }
    ~Friend3() { cnt--; }
    template<typename U> friend void counts();
    template<typename U> friend void reports(U & f);
    template<typename U, typename V> friend void show(const U & u, const V & v);
};

template<typename T>
int Friend3<T>::cnt = 0;

template<typename U>
void counts() {
    std::cout << "template counts: " << Friend3<U>::cnt << std::endl;
}

template<typename U>
void reports(U & f) {
    std::cout << f.item << std::endl;
}

template<typename U,typename V>
void show(const U & u, const V & v) {
    std::cout << u.item << ", " << v.item << std::endl;
}
#endif // CLASSTEMPLATE_H_