[TOC]

# Unit 3. 成员函数

> 前面介绍过类成员函数的声明与实现，本章将介绍一些特殊点的成员函数。

## const 成员函数与 this 指针

### const 成员函数 —— 不会修改参数的成员函数

先声明一个 Demo 类：

```cpp
#ifndef CONST_OBJECT_H_
#define CONST_OBJECT_H_
#include <string>
// const 成员函数
class Demo {
private:
    int value;
    std::string id;
public:
    Demo();
    Demo(int, std::string);
    ~Demo();
    void show();
};
Demo::Demo() {
    value = 0;
    id = "no id";
}

Demo::Demo(int v, std::string s) {
    value = v;
    id = s;
}

Demo::~Demo() {
    std::cout << "Class Demo's Destructor." << std::endl;
}

void Demo::show() {
    cout << "Value is " << value << ". ID is " << id << std::endl;
}
#endif // CONST_OBJECT_H_
```

接下来看一段代码：

```cpp
#include "const_object.h"
#include <iostream>
int main(int argc, char** args) {
    const Demo d1 = Demo(3, "Demo1");
    d1.show(); // 报错
    return 0;
}
```

错误信息如下：

![](E:\Note\Code Language\the-cpp\picture\basic\3-1.png)

错误原因：show() 的代码无法确保调用对象不被修改，即 show 函数不保证 const 对象 d1 不会被修改。



我们以前通过将函数参数声明为 const 引用或指向 const 的指针来解决这种问题。但是这里存在语法问题 —— show() 方法没有任何参数。相反，它使用的对象是由方法调用隐式提供的。所以需要一种新的语法 —— 确保成员函数不会修改调用对象。

C++ 的解决方案是将 const 关键字放在函数的括号后面。也就是说，show() 声明和定义应该如下所示：

```cpp
class Demo {
    ...
	void show() const;
    ...
};
void Demo::show() const {
    ...
}
```

### this 指针

到目前为止，我们的成员函数都只涉及到它调用的对象，但有时候成员函数会可能会涉及到多个对象，这种情况下就会用到 C++ 的 this 指针。定义一个成员函数，比较两个 Demo 对象的 value 值，并返回值较大的那个对象：

```cpp
const Demo& Demo::max(const Demo & d) const {
    if (d.value > value)
        return d;
    return ???;
}
```

该函数隐式地访问一个对象(调用对象)，显式地访问另一个对象(参数)，并返回其中一个对象的引用。括号中的 const 表示该函数不会修改参数；括号后的 const 表明该函数不会修改调用对象；由于该函数返回两个 const 引用中的一个，因此返回类型也应该是 const 引用。

其中，d.value 是参数的 value，value 是调用 max() 的对象的 value。如果参数的 value 比调用对象的 value 大，那么就返回引用参数，否则返回调用该方法的对象。但问题在于如何表示调用对象？如果调用 d1.max(d2)，则 d 是 d2 的引用，但 d1 没有别名。

C++ 解决这个问题的方法是 —— 使用被称为 this 的特殊指针。this 指针指向用来调用成员函数的对象(this 被作为隐藏参数传递给函数)。这样，函数调用 d1.max(d2) 将 this 设置为对象 d1 的地址。一般来说，所有类的成员函数都将 this 指针设置为调用它们的对象的地址。max() 中的 value 其实就是 this->value 的简写。

下图是《C++ Primer Plus》中关于 this 的图解：
![](E:\Note\Code Language\the-cpp\picture\basic\3-2.png)

```cpp
const Demo& Demo::max(const Demo & d) const {
    if (d.value > value)
        return d;
    return *this;
}
```

顺便说一下，了解 this 指针就可以更深入的了解 C++ 的工作方式。C++ 在处理方法的定义时，会进行一些转换。例如，将 max() 方法转换为下面的形式：

```cpp
const Demo& max(const Demo* this, const Demo& d){}; 
```

即将 Demo:: 限定符转换成函数参数(指向 Demo 的 this 指针)，然后用这个指针来访问类成员。

同样的，在调用方法的时候，也会进行一些转换：

```cpp
d1.max(d2);
// 转换为
max(&d1, d2);
```

这样就将调用对象的地址赋值给 this 指针。

## 运算符重载

### 运算符重载的介绍

C++ 允许将标准的运算符用于类对象，例如 +、= 等。运算符重载是一种形式的 C++ 多态，能够使对象操作更美观。运算符重载其实是一种特殊的成员函数。

**什么是多态**：字面意思就是一种事物有多种形态。对于 C++ 来说，就是指调用函数时，会根据参数的不同来执行不同的函数。其中函数重载就是一种常见的多态，另外一种常见的多态会在继承相关章节的知识中介绍。

实际上，很多 C++ 运算符已经被重载了，例如，将 * 运算符，如果它的运算对象为地址，将得到存储在这个地址中的值；但如果它的运算对象为两个数字时，得到的将是它们的乘积。C++ 允许将运算符重载扩展到用户自定义类型，例如，允许使用 + 将两个对象相加。重载运算符可使得代码看起来更自然。例如，将两个数组相加会是一种常见的运算，通常，需要使用 for 循环来实现。

```cpp
for (int i = 0; i < 20; i++)
  c[i] = a[i] + b[i];
```

但在 C++ 中可以定义一个表示数组的类，并重载 + 运算符，于是就可以用这样的语句：

```cpp
c = a + b;
```

要重载运算符，就需要使用被称为运算符函数的特殊函数形式，格式如下：

```cpp
operatorop(arg_list)
```

其中，op 为需要重载运算符，例如，operator+() 重载+运算符。op 必须是有效的 C++ 运算符，不能虚构一个新的符号。

例如，假设有一个 Demo 类，并为它定义了一个 operator+() 的成员函数，以重载 + 运算符，以便能够将两个 Demo 对象相加，如果 d1、d2、d 都是 Demo 类的对象，则可以编写这样的等式：

```cpp
d = d1 + d2;
```

编译器发现操作数是 Demo 类的对象，因此在使用 + 运算符时会用相应的 operator+() 替换 + 运算符，即上述代码和一下代码等价：

```cpp
d = d1.operator+(d2);
```

### 运算符重载的示例

定义一个 Time 类，该类包含 hours 和 minutes 两个数据，假设有一个 Time 对象 t1 表示 2 小时 25 分钟，另一个 Time 对象 t2 表示 2 小时 40 分钟，想要将两个时间相加，但相加的两个对象是 Time 对象，与内置类型不匹配，不能直接使用 + 运算符，接下来的演示将先采用之前学过的成员函数来实现相加操作，之后再演示一下运算符重载的代码，对比感受一下运算符重载的效果。

#### 使用成员函数的示例

```cpp
#ifndef MYTIME1_H_
#define MYTIME1_H_

class Time {
private:
    int hours;
    int minutes;
public:
    Time();
    Time(int hours, int minutes);
    ~Time();

    void show() const;
    void modify(int hours, int minutes);
    void addHours(int hours);
    void addMinutes(int minutes);
    Time sum(const Time & t) const;
};
#endif // MYTIME1_H_
#include "mytime1.h"
#include <iostream>
Time::Time() {
    this->hours = this->minutes = 0;
}

Time::Time(int hours, int minutes) {
    std::cout << "Time Constructor, hours = " << hours << " minutes = " << minutes << std::endl;
    if (hours < 0 || hours > 24) {
        std::cout << "Hour out of range. It's set 0" << std::endl;
        hours = 0;
    }
    if (minutes < 0 || minutes > 60) {
        std::cout << "Hour out of range." << std::endl;
        minutes = 0;
    }
        std::cout << "Minute out of range." << std::endl;
    this->hours = hours;
    this->minutes = minutes;
}

Time::~Time() {
    std::cout << "Destructor." << std::endl;
}

void Time::addHours(int h) {
    this->hours = (this->hours + h) % 24;
}

void Time::addMinutes(int m) {
    this->minutes = this->minutes + m;
    if (this -> minutes > 60) {
        this->hours++;
        this->hours %= 24;
        this->minutes %= 60;
    }
}

void Time::show() const {
    std::cout << this->hours << " hours, " << this->minutes << " minutes." << std::endl;
}

void Time::modify(int h, int m) {
    if (h < 0 || h > 24) {
        std::cout << "Hour out of range. Don't modify." << std::endl;
        return;
    }
    if (m < 0 || m > 60) {
        std::cout << "Minute out of range. Don't modify." << std::endl;
        return;
    }
    this->hours = h;
    this->minutes = m;
}

Time Time::sum(const Time &t) const {
    Time tmp;
    tmp.minutes = t.minutes + minutes;
    tmp.hours = (t.hours + hours + tmp.minutes / 60) % 24;
    tmp.minutes %= 60;
    return tmp;
}
```

来看一下 sum() 函数代码。需要注意，参数中使用了引用，但返回类型却不是引用。

参数中使用引用是为了提高效率，也可以按值传递 Time 对象也可以实现相同的功能，但比起按引用传递，效率低，使用的内存也多。

然而，返回值不能是引用。因为 sum() 函数中将创建一个新的 Time 对象(tmp)，来保存另外两个 Time 对象的和。如果返回类型是 Time &，则返回的是 tmp 对象的引用，但 tmp 对象是局部变量，在函数结束时将被删除，因此引用将指向不存在的对象。而返回类型为 Time 意味着程序在删除临时对象 tmp 之前构造它的拷贝，调用函数将返回该拷贝。

> 警告：不要返回指向局部变量或临时对象的引用。函数执行完毕之后，局部变量和临时对象将消失，引用将指向不存在的数据。

```cpp
// 对Time类成员函数的测试
#include "mytime1.h"
#include <iostream>
int main(int argc, char ** args) {
    Time t1;
    Time t2(2, 40);
    Time t3 = Time(5, 55);

    std::cout << "t1 = ";
    t1.show();
    std::cout << "t2 = ";
    t2.show();
    std::cout << "t3 = ";
    t3.show();

    t1 = t2.sum(t3);
    std::cout << "t1 + t2 = ";
    t1.show();
    return 0;
}
```

```
Default Constructor.
Time Constructor, hours = 2 minutes = 40
Time Constructor, hours = 5 minutes = 55
t1 = 0 hours, 0 minutes.
t2 = 2 hours, 40 minutes.
t3 = 5 hours, 55 minutes.
Default Constructor.
Destructor.
t1 + t2 = 8 hours, 35 minutes.
Destructor.
Destructor.
Destructor.
```

#### 使用运算符重载示例

将 Time 类转换成重载的加法运算符很容易，只要将成员函数 sum() 的名称改为 operator+() 即可。

```cpp
#ifndef MYTIME2_H_
#define MYTIME2_H_

class Time {
private:
    int hours;
    int minutes;
public:
    Time();
    Time(int, int);
    ~Time();
    void addHour(int);
    void addMinute(int);
    void show() const;
    void modify(int, int);
    Time operator+(const Time &) const;
};
#endif // MYTIME2_H_
Time Time::operator+(const Time & t) const {
    Time sum;
    sum.minutes = this->minutes + t.minutes;
    sum.hours = (this->hours + t.hours + sum.minutes / 60) % 24;
    sum.minutes %= 60;
    return sum;
}
```

和 sum() 一样，operator+() 也是由 Time 对象调用的，它将第二个 Time 对象作为参数，并返回一个 Time 对象。因此，可以像调用 sum() 那样调用 operator+() 方法。

```cpp
t1 = t2.operator+(t3);
```

但是在该方法命名为 operator+() 之后，也可以使用运算符表示法：

```cpp
t1 = t2 + t3;
```

这两种表示法都将调用 operator+() 函数。在运算符表示法中，运算符左侧的对象是调用对象，运算符右侧的对象是作为参数被传递的对象。

```cpp
#include "mytime2.h"
#include <iostream>
int main(int argc, char ** args) {
    Time t1 = Time(2, 40);
    Time t2 = Time(5, 55);
    Time t3 = Time(3, 28);

    Time t4 = t1 + t2;
    Time t5 = t1.operator+(t3);
    std::cout << "t4 = ";
    t4.show();
    std::cout << "t5 = ";
    t5.show();
    return 0;
}
```

```
Time Constructor, hours = 2 minutes = 40
Time Constructor, hours = 5 minutes = 55
Time Constructor, hours = 3 minutes = 28
Time Default Constructor
Time Default Constructor
t4 = 8 hours, 35 minutes.
t5 = 6 hours, 8 minutes.
Destructor
Destructor
Destructor
Destructor
Destructor
```

总之，operator+() 函数可以使用函数表示法或者运算符表示法来调用它。

### 问题

对于两个对象以上的加法，可以像基本运算符那样连加吗？

```cpp
t4 = t1 + t2 + t3; // 这是有效的吗?
```

答：可以的。



我们来看一下上述语句将如何转换为函数调用。

《C++ Primer Plus》第387页：由于 + 运算符是从左向右结合运算符，因此上述语句将首先被转换成下面这样：

```cpp
t4 = t1.operator+(t2 + t3);
```



疑问一：从理论上来说，+ 运算符是从左向右的结合性，因此不应该是先算 t1 + t2，然后将得到的表示 t1 + t2 的临时对象与 t3 去相加吗？为什么先计算 t2 + t3？

疑问二：根据代码实际测试，t1 + t2 + t3 是先计算 t1 + t2 的值。不确定是书上写错了，还是 C++11 对其有所修改。

### 运算符重载的限制

并不是所有的运算符都能被重载，下面介绍 C++ 对用户自定义的运算符重载的限制：

1. **重载后的运算符必须至少有一个操作数是用户自定义的类型**。这是为了防止用户为标准类型重载运算符，影响标准类型的使用。
2. **使用运算符时不能违反运算符原来的句法规则**。例如，% 运算符的操作数为两个，不能将 % 运算符重载为使用一个操作数的运算符。
3. **不能创建新的运算符**。
4. **不能重载的运算符**：sizeof 运算符、成员运算符 .、成员指针运算符 .*、作用域解析符 ::、条件运算符 ?:、const_cast、dynamic_cast、static_cast、reinterpret_cast、typeid。
5. 大部分可重载的运算符都不必是成员函数，还可以定义为非成员函数，一般来说，非成员函数应是友元函数，这样它才能直接访问类的私有数据。但有四个运算符必须作为成员函数来重载：赋值运算符 =、函数调用运算符 ()、下标运算符 []、指针访问类成员的运算符 ->。

### 小结

1. C++ 允许用户重载运算符，重载后的运算符必须至少有一个操作数是用户自定义的类型，并且不能修改运算符的操作数。
2. 使用 operator\[op]() 来定义重载运算符，其中 \[op] 使用需要被重载的运算符来代替。
3. 不能被重载的运算符：sizeof  .   ::  ?:  .*。
4. 只能作为成员函数来重载的运算符：=  ()  []  ->。
5. 重载运算符可以作为成员函数，也可以作为非成员函数。作为成员函数时，参数数目比运算符操作数少一个，因为会将 *this 作为隐式参数；作为非成员函数时，参数数目等于操作数数目，并且第一个参数就是最左侧的操作数。通常作为非成员函数时，应声明为友元函数，这样可以直接访问类的私有成员。关于友元函数后面会专门讲。

## 友元函数

C++ 控制对类对象私有部分的访问。通常，公有类方法提供唯一的访问途径，但是有时候这种限制太严格，以致于不适合特定的编程问题。在这种情况下，C++ 提供了另外一种形式的访问权限：友元。友元有三种形式 —— 友元函数、友元成员函数、友元类。这里只介绍友元函数。

当函数被声明为类的友元函数，可以赋予该函数与类的成员函数相同的访问权限。

### 为什么需要用友元函数？

在为类重载二元运算符时常常需要用到友元函数。例如，为一个时间类 Time 重载乘法运算符，使其可以乘以一个实数，部分代码如下所示：

```cpp
class Time {
private:
    int hours;
    int minutes;
public:
    ...;
    Time operator*(double n) const;
    void show() const;
};
void Time::show() const {
    std::cout << this->hours << " hours, " << this->minutes << " minutes. Address is " << this << std::endl;
}
Time Time::operator*(double n) const {
    Time res; 
    long totalMinutes = (long) (n * (hours * 60 + minutes));
    res.hours = totalMinutes / 60;
    res.minutes = totalMinutes % 60;
}
```

这个重载的乘法运算符使用的是两个不同的类型，即乘法运算符将一个 Time 值与一个 double 值结合在一起。这限制了乘法运算符的使用 —— Time 对象必须在乘法运算符的左侧，double 值必须在乘法运算符右侧。

```cpp
A = B * 2.5; // 正确
A = 2.5 * B; // 错误
```

2.5 * B 并不对应 operator*() 成员函数，因为 2.5 不是 Time 对象。

解决这个问题的一种方式是，告知每个人，只能按照 B * 2.5 这种格式编写，这是一种对服务器友好-客户警惕的解决方案。另一种方式则是采用非成员函数来重载乘法运算符。非成员函数不是由对象调用，它使用的所有值都是显式参数。

使用非成员函数重载乘法运算符可以按照所需的顺序来获得操作数(先 double 值，后 Time 对象)，但是非成员函数无法直接访问类的私有数据。可以通过提供一系列的公有接口让非成员函数间接执行一些操作，但更常用的是利用一类特殊的非成员函数 —— 友元函数，友元函数可以直接访问类的私有成员。

### 创建友元函数

和普通函数、类的成员函数一样，创建友元函数分为两步：

- 友元函数的函数声明；
- 友元函数的函数定义(实现细节)。

创建友元函数的第一步，需要将友元函数的原型放在类声明中，并在其原型声明的前面加上关键字 friend。

```cpp
class Time {
private:
    int hours;
    int minutes;
public:
    ...;
    Time operator*(double n) const;
    friend Time operator*(double, const Time &);
    void show() const;
};
```

这个原型意味着两点：

- 虽然该 operator*() 是在类声明中声明的，但它不是成员函数，因此不能用成员运算符来调用；
- 虽然 operator*() 不是成员函数，但它与成员函数的访问权限相同。



创建友元函数的第二步需要编写函数定义。因为友元函数不是类的成员函数，因此在编写函数定义的时候，不必在函数名之前使用 Time:: 限定符。另外，不要在函数定义处使用 friend 关键字。

```cpp
Time operator*(double n, const Time & t) {
    Time res;
    long totalMinutes = (long) (n * (t.hours * 60 + t.minutes));
    res.hours = totalMinutes / 60;
    res.minutes = totalMinutes % 60;
    return res;
}
```

有了上述声明和定义之后，下面的语句：

```cpp
A = 2.5 * B;
```

将转换为如下的语句，从而调用刚才定义的非成员友元函数：

```cpp
A = operator*(2.5, B);
```

> 乍一看，友元函数违反了 OOP 数据隐藏的原则，因为友元机制允许非成员函数访问私有数据，但这个观点太片面了，应该将友元函数看做类扩展接口的组成部分。只有在类声明中才能够决定那一个函数是本类的友元函数，因此类声明仍然控制了那些函数可以访问私有成员。总之，类方法和友元只是表达类接口的两种不同机制。

### 补充：非成员函数的运算符重载解决参数顺序问题

上面的例子只是为了演示友元函数，事实上，在定义了 Time 类的成员函数 operator*(double) 的基础下，可以通过普通的非成员函数来重载乘法运算符。

```cpp
Time operator*(double n, const Time & t) {
    return t * n;
}
```

之前的函数定义中显式地访问了 Time 的私有成员，所以该运算符重载必须声明为友元。但这个版本的则是通过调用 Time 类的成员函数 operator*(double) 来实现的，并不需要显式地访问 Time 的私有成员，因此不必声明为友元。不过，将该版本声明为友元也是一个好主意，这样它将成为正式接口的组成部分。

> 提示：如果要为类重载运算符，并将非类的项作为第一个操作数，则可以用友元函数来反转操作数的顺序。 

### 最常用的友元函数 —— 重载 << 运算符

一个很有用的类的特性是，可以对 << 运算符重载，使之能与 cout 一起来显示对象的内容。与前面介绍的示例相比，这种重载要更复杂些。

假设 time 是一个 Time 对象，为了显示 Time 的内容，前面使用的是 show() 函数，现在希望可通过下面这样的操作来显示 Time 的内容。

```cpp
std::cout << time << std::endl;
```

之所以可以这样做，是因为 << 运算符也是 C++ 可以重载的运算符之一。实际上，它已经被重载过很多次了。最初，<< 运算符是 C++ 的左移运算符。ostream 类对该运算符进行了重载，将其转换为一个输出工具。前面讲过，cout 是一个 ostream 类的对象，它是智能的，能够识别所有的 C++ 基本类型，这是因为对于每种基本类型，ostream 类声明中都包含了相应的重载的 operator<<() 成员函数。因此，要是 cout 能够识别 Time 对象，一种方法是将一个新的函数运算符定义添加到 ostream 类声明中，但修改 iostrea 文件是一个危险的注意，这样做会在标准接口上浪费时间。相反，应该让 Time 类声明来让 Time 类知道如何使用 cout —— 在 Time 类中定义一个友元函数。

#### 重载 << 运算符(Version 1)

要使 Time 类知道使用 cout，必须使用友元函数。这是因为`cout << time `语句，使用两个对象，并且第一个对象是 ostream 类对象(cout)。如果是声明为成员函数，则第一个对象必须是 Time 对象；如果是声明为普通的非成员函数，可以使得第一个对象为 ostream 类对象，但是不能直接访问 Time 的私有成员。

```cpp
class Time {
private:
    int hours;
    int minutes;
public:
    // ...
    friend void operator<<(std::ostream & out, const Time &);
};
void operator<<(std::ostream & out, const Time & t) {
    std::cout << t.hours << " hours, " << t.minutes << " minutes. Address is " << this << std::endl;
}
```

这样就可以使用下面的语句打印数据了：

```cpp
std::cout << time;
```

> operator<<() 虽然是友元函数，但是它只在 Time 类声明中被声明，并没有在 ostream 类中声明，因此，它只是 Time 类的友元函数，并不是 ostream 类的友元函数。这也是因为在 operator<<() 的函数定义中直接访问了 Time 类对象的私有数据，而对于 ostream 对象只是当做一个整体来使用，并没有访问私有成员。

#### 重载 << 运算符(Version 2)

在 Version 1 中存在一个问题， 虽然`cout << time;`可以正常使用，但这种实现不允许像通常那样将重新定义的 << 运算符和 cout 一起使用：

```cpp
cout << "Time is " << time << endl; // 报错
```

上面的语句，实际上等同于：

```cpp
((cout << "Time is ") << time) << endl; 
```

由于 Version 1 中定义的 operator<<() 返回值是 void，因此执行到 ((cout << "Time is ") << time) 时将返回 void，导致最后的 << 运算符左侧是 void，因此报错。

```cpp
class Time {
private:
    int hours;
    int minutes;
public:
    // ...
    friend std::ostream & operator<<(std::ostream & out, const Time &);
};
std::ostream & operator<<(std::ostream & out, const Time & t) {
    std::cout << t.hours << " hours, " << t.minutes << " minutes. Address is " << &t << std::endl;
    return out;
}
```

### 小结

1. 友元函数的函数原型位于在类声明中，但并不是类的成员函数，在声明函数原型时，需要使用 friend 关键字。
2. 友元函数的函数定义不需要 friend 关键字和 :: 运算符，和普通非成员函数是一样的。
3. 友元函数可以直接访问类的私有成员。
4. 通常在运算符重载中使用友元函数的情况是：重载的运算符的第一个参数不是该类的对象。

## 练习 —— 矢量类

### 矢量类的代码

由于无法用一个数来表示矢量，因此应该创建一个类来表示矢量。矢量的相加和相减与普通数学运算有相似之处，所以应重载运算符使之能用于矢量。

本节将实现一个二维矢量，描述二维矢量需要有两个数，但有两种方式：

1. 用长度和角度表示(极坐标)；
2. 用水平分量 x 和垂直分量 y 表示(直角坐标)。

```cpp
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
        cout << "Default Constructor.\n";
        x = y = ang = mag = 0.0;
        mode = RECT;
    }

    Vector::Vector(double n1, double n2, Mode form) {
        cout << "Constructor. ";
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
            cout << "构造方法 Vector() 的第三个参数是无效的. 对象的值将被设置为 0, 并且采用直角坐标系.";
            x = y = ang = mag = 0.0;
            mode = RECT;
        }
        cout << std::endl;
    }

    Vector::~Vector() {
        cout << "Destructor.\n";
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
            cout << "reset() 的第三个参数是无效的. 对象的值将被设置为 0, 并且采用直角坐标系.\n";
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
            out << "(x, y) = (" << vec.x << ", " << vec.y << ")" << std::endl;
        } else if (vec.mode == Vector::POL) {
            out << "(mag, ang) = (" << vec.mag << ", " << vec.ang * RadToDeg << ")\n";
        } else {
            out << "Vector object mode is invalid.\n";
        }
        return out;
    }
}
```

也可以以另一种方式来设计这个类。例如，在对象中只存储直角坐标系，不保存极坐标系，在需要用到极坐标系坐标时使用 getAngVal() 和 getMagVal() 来计算极坐标系。

在重载的 +、-、* 运算符的定义中是通过类构造方法来实现的。如果方法通过计算得到一个新的类对象，则应该考虑是否可以使用类构造函数来完成这种工作。这样不仅可以避免麻烦，而且可以确保新的对象是按照正确的方式创建的。

### 利用矢量类实现随机漫步问题

```cpp
using VECTOR::Vector;
using std::cout;
using std::cin;
using std::endl;

srand(time(0)); // 设置种子
Vector result(0, 0, VECTOR::Vector::RECT); // 采用直角坐标系记录当前所在位置
Vector step; // 记录当前随机的矢量
unsigned long steps = 0; // 记录走过的总步数

double target; // 记录目标距离
double dstep; // 记录每一步的步长

cout << "请输入目标距离(按 q 表示退出):";
while (cin >> target) {
    cout << "请输入步长:";
    if (!(cin >> dstep)) {
        cout << "输入的步长无效,程序将退出.";
        break;
    }

    // 如果距离没有达到目标距离, 继续走下一步
    while (result.getMagVal() < target) {
        // 随机生成下一步的方向, 并利用步长和方向按照极坐标系创建实例
        step = Vector(dstep, rand() % 360, Vector::POL);
        // 往 step 指示方向位移一步
        result = result + step;
        // 走的步数+Unit1
        steps++;
    }

    cout << "经过 " << steps << " 步之后到达指定的距离, 当前位置如下所示: " << endl;
    cout << "(x, y) = (" << result.getXVal() << ", " << result.getYVal()
        << ") or (mag, ang) = (" << result.getMagVal() << ", " << result.getAngVal()
        << ")\n";
    cout << "移动的平均步长为: " << result.getMagVal() / steps << endl;

    // 重置步数和当前所在位置
    steps = 0;
    result.reset(0, 0, Vector::RECT);
    cout << "请输入目标距离(按 q 表示退出):";
}
cout << "Bye!\n";
cin.clear();
```

time(0) 返回当前系统时间，srand(time(0)) 将当前系统时间作为种子值，rand() 函数将根据 srand() 设置的种子值返回一个伪随机数。

该程序使用 result 记录行走者当前的位置情况。内循环每轮将 step 矢量设置新的方向，并将它与当前的 result 矢量相加。当 result 的长度超过指定的距离之后，该循环结束。

`result = result + step;`这条语句将 result 设置为 RECT 模式，而不管 result 和 step 的初始模式是什么，这是在 + 运算符重载的实现决定的，如果不希望这样实现，可以修改 operator+() 方法的实现。

如果想要将行走者一系列的位置存储到文件中也是很容易的，只需要包含 fstream 头文件，并声明一个 ofstream 对象，将其同一个文件关联起来，然后使用 << 运算符将位置记录输出到文件中：

```cpp
#include <fstream>
...
ofstream fout;
fout.open("walker.txt");
fout << result << endl;
```

## 类的类型转换

### 转换构造函数

C++ 基本数据类型之间是可以经过一些类型转换的。将一个基本数据类型变量的值赋给另一个基本数据类型变量时，如果这两种类型兼容，则 C++ 自动将这个值转换为接收变量的类型；如果不兼容，C++ 不会自动转换，此时可以使用强制类型转换，不过要注意这种转换是否有意义。而 C++ 的目标之一就是使用类对象可以像使用内置类型变量一样，因此对于类型转换这一部分，C++ 也提供了一种类型转换的机制。通过这个机制，可以将类定义成与基本数据类型 or 另一个类相关，使得从一种类型转换成另一种类型是有意义的。在这种情况下，程序员可以指示 C++ 如何自动进行转换，或通过强制类型转换来完成。

实现类的类型转换的机制是通过一种特殊的构造函数来完成的 —— 只接受一个参数的构造函数。**一个构造函数接收一个不同于其类类型的形参，可以视为将其形参转换成类的一个对象。像这样的构造函数称为转换构造函数。**

```cpp
#ifndef STONE_H_
#define STONE_H_
class Stone {
private:
    static const int LBS_PER_STN = 14; // Unit1 英石 = 14 磅
    int stone; // 英石
    double pds_left; // 剩余的磅数
    double pounds; // 磅
public:
    Stone();
    Stone(double p);
    Stone(int s, double pl);
    ~Stone();
    // 以磅的形式展示数据
    void show_stn() const;
    // 以英石和磅的形式展示数据
    void show_lbs() const;
};
#endif // STONE_H_
#include "stone.h"
#include <iostream>
Stone::Stone() {
    stone = pds_left = pounds = 0;
}
Stone::Stone(double p) {
    pounds = p;
    stone = (int) p / LBS_PER_STN;
    pds_left = p - stone * LBS_PER_STN;
}

Stone::Stone(int s, double pl) {
    stone = s;
    pds_left = pl;
    pounds = s * LBS_PER_STN + pl;
}

Stone::~Stone() {
    std::cout << "Destructor.\n";
}

void Stone::show_stn() const {
    std::cout << stone << " stone, " << pds_left << " pounds\n";
}

void Stone::show_lbs() const {
    std::cout << pounds << "pounds.\n";
}
```

`Stone(double p);`这个构造函数用于将 double 类型的值转换为 Stone 类型，也就是说可以这样编写代码：

```cpp
Stone s1;
s1 = 27.3;
```

程序将使用构造函数`Stone(double p);`来创建一个临时的 Stone 对象，并将 27.3 作为初始化的值，然后采用逐成员赋值的方式将该临时对象的内容赋值到 s1 中。这一个过程被称为隐式转换，或者自动转换，因为它是自动进行的，不需要显式强制类型转换。这种只接受一个参数的构造函数被称为**转换函数**。



下面的构造函数接受两个参数，因此不是转换函数，不能用来转换类型：

```cpp
Stone(int s, double pl);
```

然而，如果给第二参数提供默认值，它便可用于转换 int。



将构造函数用于自动类型转换函数似乎是一项不错的特性。然而，当程序员拥有更丰富的 C++ 经验时，将发现这种自动特性并非总是合乎需要的，因为这会导致意外的类型转换。因此，C++ 新增了关键字 explicit，用于关闭这种特性。和 friend 关键字一样，explicit 只需要在类声明中的函数原型处使用，不能出现在类外的成员函数实现处。

> explicit adj 明确的

```cpp
class Stone {
	...;
    explicit Stone(double p);
};

Stone::Stone(double p) {
    pounds = p;
    stone = (int) p / LBS_PER_STN;
    pds_left = p - stone * LBS_PER_STN;
}
```

当构造函数`Stone(double p);`被 explicit 修饰之后，将关闭隐式类型转换，但仍然允许显式转换。

![](E:\Note\Code Language\the-cpp\picture\basic\3-3.png)

> 不只是基本数据类型，只要定义相应的转换构造函数，可以将用户自定义的其他类型转换为 Stone 对象。

### 转换函数

前面的程序展示了如何将其他类型转换为 Stone 对象，那么可以做相反的转换吗？也就是说，是否可以将 Stone 对象转换为 double 值？就像下面做的那样：

```cpp
Stone s1 = Stone(25.7);
double d = s1; // 可以吗？
```

可以这样做，但是不能使用转换构造函数。转换构造函数只能用于从某种类型(包括基本数据类型以及其他类类型)到类类型的转换。要想将类类型转换为其他类型，必须使用特殊的 C++ 运算符函数 —— 转换函数。

**如何创建转换函数？** 要将类类型转换为 typeName 类型，需要使用这种形式的转换函数：

```cpp
operator typeName();
```

需要注意几点：

- 转换函数和构造函数一样，没有返回类型；
- 转换函数必须是类方法；
- 转换函数没有参数。

例如，转换为 double 类型的函数的原型如下：

```cpp
operator double();
```

typeName(上例中是 double) 指出了要转换成的类型，因此不需要指定返回类型。转换函数是类方法意味着：它需要通过类对象来调用，从而告知函数要转换的值。因此，函数不需要参数，因为参数是隐式传递的。



添加转换函数之后的 Stone 类声明：

```cpp
#ifndef STONE_H_
#define STONE_H_
#include <iostream>
class Stone {
private:
    static const int LBS_PER_STN = 14; // Unit1 英石 = 14 磅
    int stone; // 英石
    double pds_left; // 剩余的磅数
    double pounds; // 磅
public:
    Stone();
    explicit Stone(double p);
    Stone(int s, double pl);
    ~Stone();
    // 以磅的形式展示数据
    void show_stn() const;
    // 以英石和磅的形式展示数据
    void show_lbs() const;
    operator double() const;
};

Stone::Stone(double p) {
    pounds = p;
    stone = (int) p / LBS_PER_STN;
    pds_left = p - stone * LBS_PER_STN;
}

Stone::operator double() const {
    return pounds;
}
#endif // STONE_H_
// 对转换函数的测试:
int main(int argc, char ** args) {
    Stone s1 = Stone(23.9);
    double pound = s1;
    std::cout << "Convert to double => " << pound << std::endl;
    return 0;
}
// 输出结果:
// Convert to double => 23.9
```

和转换构造函数一样，转换函数也有其优缺点。提供执行自动、隐式转换的函数所存在的问题是：在用户不希望进行转换时，转换函数也可能进行转换；当定义了多个转换函数时，使用隐式转换可能有二义性的问题。

原则上说，最好使用显式转换，而避免隐式转换。学习过转换构造函数之后，应该可以想到 explicit 关键字，但需要注意的是在 C++98 中，关键字 explicit 不能用于转换函数，不过 C++11 消除了这种限制。因此，在 C++11 中，可以将转换运算符生命为显式的：

```cpp
class Stone {
	...
    explicit operator double() const;
};
```

有了这些声明之后，转换类型时需要强制类型转换。

另一种方法是，用一个功能相同的非转换函数来替换转换函数，这样仅显式调用该函数才会转换类型。

```cpp
Stone::operator double();
// 替换为:
double Stone::StoneToDouble();
```

使用时：

```cpp
Stone s1 = Stone(23.5);
double d1 = s1; // 报错
double d2 = s1.StoneToDouble(); // 正确
```

### 小结

总之，C++ 为类提供了下面的类型转换：

- 只有一个参数的类构造函数用于将该构造函数参数类型转换为该类的类型。在构造函数的声明中使用 explicit 关键字将关闭隐式转换，只允许使用显式转换。
- 被称为转换函数的特殊的类成员运算符函数，用于将类对象转换成其他类型。转换函数是类成员函数，没有返回值、没有参数、名为 operator typeName()，其中 typeName 是需要转换成的类型。将类对象赋给 typeName 类型的变量or将其强制转换为 typeName 类型时，该转换函数将被调用。C++11 之后，可以用 explicit 关闭隐式转换。



## 复习

**this 和 const**

所有的成员函数其实都包含一个隐式参数 *this。由于不会显式传递调用函数的对象，因此不能在参数前面加上 const 表示成员函数不会修改调用该函数的对象，而是在函数后面加上 const 关键字。

```cpp
void Class::show() const;
// =>
void show(const Class &);
```



**1.成员函数的声明：**与普通函数声明类似

```cpp
class Demo {
private:
    int value;
    double num;
public:
    int showFunc(int);
}
```

**2.成员函数的实现：**与普通成员函数的实现有一定区别

```cpp
int Demo::showFunc(int) {
	// 实现细节
}
```

**3.内联成员函数：**函数实现位于类声明中的成员函数是隐式的内联函数；如果想要显式声明内联成员函数，可以在类声明中正常声明成员函数，在实现成员函数时加上 inline 关键字，并且成员函数的实现应该和类声明放在同一个文件中。

```cpp
class Demo {
private:
    int value;
    double num;
public:
    int showFunc(int);
}

inline int Demo::showFunc(int v) {
    // 实现细节
}
```

**4.构造函数：**构造函数在创建对象时被自动调用。

特点：构造函数的函数名与类同名；没有返回类型；可以声明特征值不同的构造函数(重载)。

注意：当程序员没有声明构造函数，编译器会生成一个默认构造函数；一旦程序员声明了构造函数，编译器就不会再生成默认构造函数。

比较特殊的几个构造函数 —— 默认构造函数，复制构造函数、转换构造函数。

```cpp
class Demo {
private:
    int value;
    double num;
public:
	Demo();
    Demo(int, double);
}    
```

**5.析构函数：**析构函数在对象被销毁时被编译器自动调用。

特点：函数名为类名前面加上~；没有返回类型；没有参数。

注意：构造函数可以有参数，因此可以被重载，但是析构函数不接受参数，因此一个类只能有一个析构函数；通常，不需要我们编写析构函数，但是当类成员涉及动态内存分配时，需要编写析构函数。

```cpp
class Demo {
private:
    int value;
    double num;
public:
	~Demo();
}    
```

**6.运算符重载：**

```cpp
returnType operator[op](argList);
```

运算符重载的参数必须至少有一个是自定义类型；不能更改运算符的操作对象数目；运算符重载可以是成员函数，也可以是非成员函数，不过非成员函数通常被设为友元函数；. .* :: ?: sizeof 这5个运算符不能被重载。

```cpp
class Demo {
private:
    int value;
    double num;
public:
    // 成员函数的重载运算符
	Demo & operator*(double);
    // 友元函数的重载运算符
    friend std::ostream & operator<<(std::ostream &, const Demo &); 
}
// 普通非成员函数的重载运算符, 不能直接访问类的私有成员
Demo & operator+(const Demo & d1, const Demo & d2); 

/*
 * 函数实现
 */
Demo & Demo::operator*(double d) {
	// 实现细节
}
std::ostream & operator<<(std::ostream & out, const Demo & d) {
    
}
Demo & operator+(const Demo & d1, const Demo & d2) {
	// 实现细节
}
```

注意：友元函数的关键字 friend 只能出现在类内，即只能在函数声明时使用，在函数定义处不能出现 friend (explicit 关键字也一样)，详见 operator<< 的函数定义和函数实现。

**7.转换函数：**转换构造函数可以将其他类型对象转换为类类型；而转换函数则是反过来将类类型转换为其他类型。

特点：转换函数没有返回类型，因为返回的类型已经由 typeName 表明了；转换函数没有参数，因为参数其实就是通过隐式传递的 *this；转换函数必须是成员函数，因为传递的参数就是类对象。

```cpp
class Demo {
private:
    int value;
    double num;
public:
	operator typeName();
}
```

C++11 之后可以用 explicit 关键字关闭隐式转换。

<hr>

<hr>