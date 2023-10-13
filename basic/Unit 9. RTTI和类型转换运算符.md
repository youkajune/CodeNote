## RTTI(Runtime Type Identify)

### 简介

RTTI 全称 Runtime Type Identify，即运行时类型识别。这是新添加到C++中的特性之一。RTTI 的目的是为程序在运行阶段确定对象类型提供一种标准方式。很多类库已经为其类对象提供了实现这种功能的方式，但由于C++内部并不支持，因此各个厂商的机制通常不兼容。创建一种 RTTI 语言标准将使得未来的库能够彼此兼容。

### 用途

假设有一个类层次结构，其中的类都是从同一个基类派生而来的，则可以让基类指针指向其中任何一个类的对象。这样便可以调用这样的函数：在处理一些信息之后，选择一个类，并创建这种类型的对象，然后返回它的地址，这个地址可以被赋值给基类指针。如何知道这个基类指针指向的是哪个类的对象？

在回答这个问题之前，先考虑为何要知道类型。可能是希望调用类方法的正确版本，在这种情况下，只要该函数是类层次结构中所有成员都拥有的虚函数，那么就不真的需要知道对象的类型，也可以调用派生类的版本。但派生对象可能会包含非继承而来的方法，如果想要调用这样的方法，那么就无法直接使用基类指针来调用，而是需要先将基类指针转换为对应派生类对象的指针才能调用。也可能是出于某些调试目的，希望能跟踪生成的对象的类型。对于后两者，RTTI 将提供解决方案。

### 工作原理

C++提供3个支持 RTTI 的元素：dynamic_cast、typeid、type_info。
- dynamic_cast: 如果可能的话，dynamic_cast 运算符将使用一个指向基类的指针来生成一个指向派生类的指针；否则，该运算符将返回 0 —— 空指针。
- typeid: typeid 运算符返回一个指向对象的类型的值。
- type_info: type_info 结构存储了有关特定类型的信息。

只能将 RTTI 用于包含虚函数的类层次结构，原因在于只有对于这种类层次结构，才应该将派生对象的地址赋给基类指针。

> Warning: RTTI 只适用于包含虚函数的类。

下面将详细介绍这3个元素。

#### dynamic_cast

dynamic_cast 运算符是最常用的 RTTI 组件，它不能回答“指针指向的是哪类对象”这样的问题，但能回答“是否可以安全地将对象的地址赋值给指定类型的指针”这样的问题。

假设有下面这样的类层次结构：

```cpp
class Base {
    // 包含虚函数
};
class BasePlus : public Base { };
class BasePlusPlus : public BasePlus { };
```

接下来假设有这样的基类指针：

```cpp
Base * pb  = new Base();
Base * pp  = new BasePlus();
Base * ppp = new BasePlusPlus();
```

最后，对于下面的类型转换：

```cpp
BasePlusPlus * p1 = (BasePlusPlus *) ppp; // #1
BasePlusPlus * p2 = (BasePlusPlus *) pb;  // #2
BasePlus * p3 = (BasePlusPlus *) ppp;     // #3
```

哪些是安全的？根据类声明，它们可能都是安全的，但只有那些指针类型与对象类型(or 对象的直接或间接基类的类型)相同的类型转换才一定是安全的。例如，在上例中，#1 是安全的，因为它将 BasePlusPlus 指针指向 BasePlusPlus 的对象。#2 是不安全的，因为它将基类(Base)对象的地址赋值给派生类(BasePlusPlus)指针。因此，程序将会期望基类对象包含派生类的特征，而这通常是不可能的。#3 是安全的，因为它讲派生类(BasePlusPlus)对象的地址赋值给基类(BasePlus)指针。公有继承确保了一个 BasePlusPlus 对象是一个直接基类(BasePlus)对象，同时也是一个间接基类(Base)对象。因此，将它的地址赋给这3种类型的指针都是安全的。虚函数机制确保了这三种指针中的任何一种指针指向 BasePlusPlus 对象时，调用的虚函数都是 BasePlusPlus 版本的。

> 注意，与问题“指针指向的是哪类对象”相比，问题“类型转换是否安全”更通用，也更有用。通常想知道类型的原因在于：知道类型之后，就可以知道调用特定的方法是否安全。要调用方法，类型并不一定要完全匹配，而可以是定义了方法的虚拟版本的基类类型。

先来看一下 dynamic_cast 的使用语法：

```cpp
BasePlus * pbp = dynamic_cast<BasePlus *> (pb);
```

指针 pb 的类型是否可以安全地被转换为 BasePlus*？如果可以，dynamic_cast 运算符将返回对象的地址；否则，返回一个空指针。

注意：通常，如果指向的对象(*pt)的类型为 Type 或者是从 Type 直接或间接派生而来的类型，则下面的表达式将指针 pt 转换为 Type 类型的指针，否则，结果为空指针(0):

```cpp
dynamic_cast<Type *> (pt)
```

下面以程序来演示这种处理。首先，定义了三个类，名称分别为 Grand、Superb、Magnificent。Grand 类定义了一个虚函数 Speak()，而其他类都重写了该虚函数。Superb 类定义了一个虚函数 Say()，而 Magnificent 也重写了它。在程序中定义了 GetOne() 函数，该函数随机创建这3种类中的某个类的对象，并对其进行初始化，然后将地址作为 Grand* 指针返回。循环将该指针赋值给 Grand* 变量 pg，然后使用 pg 指针调用 Speak() 函数。因为这个函数是 virtual，所以代码能够正确地调用指向的对象的 Speak() 版本。

```cpp
Grand* pg;
for (int i = 0; i < 5; i++) {
    pg = GetOne();
    pg->Speak();
}
```

然而，不能用相同的方法(即指向 Grand 的指针)来调用 Say()，因为 Grand 类声明中并没有定义 Say() 函数。然而，可以使用 dynamic_cast 运算符来检查是否可以将 pg 的类型安全地转换为 Surpb 指针。

```cpp
Superb * ps;
if (ps = dynamic_casst<Superb *> (pg)) {
    ps->Say();
}
```

![](../../cplusplus-note/picture/basic/9-1.png)

程序代码：

```cpp
// RTTI.h
#ifndef RTTI_H
#define RTTI_H

#include <iostream>

class Grand {
private:
    int hold;
public:
    Grand(int h = 0) : hold(h) { }
    virtual ~Grand() = default;
    virtual void Speak() const { std::cout << "I am a Grand class.\n"; }
    virtual int Value() const { return hold; }
};

class Superb : public Grand {
public:
    Superb(int h = 0) : Grand(h) { }
    virtual ~Superb() = default;
    virtual void Speak() const { std::cout << "I am a Superb class.\n"; }
    virtual void Say() const { std::cout << "I hold the Superb value of " << Value() << "!.\n"; }
};

class Magnificent : public Superb {
private:
    char ch;
public:
    Magnificent(int hold = 0, char c = 'A') : Superb(hold), ch(c) { }
    virtual ~Magnificent() = default;
    virtual void Speak() const { std::cout << "I am a Magnificent class.\n"; }
    virtual void Say() const { std::cout << "I hold the character " << ch << " and the integer " << Value() << "!\n"; }
};

#endif // RTTI_H
```

```cpp
// main.cpp
#include <ctime>
#include "RTTI.h"

/**
 * 随机生成 Grand、Superb、Magnificent 三个类中的某个类的对象
 **/
Grand *GetOne() {
    Grand * p;
    int temp = std::rand();
    switch (temp % 3) {
        case 0:
            p = new Grand(temp);
            break;
        case 1:
            p = new Superb(temp);
            break;
        case 2:
            p = new Magnificent(temp, 'A' + temp % 26);
            break;
        default:
            p = nullptr;
    }
    return p;
}

/**
 * RTTI dynamic_cast 运算符的演示程序
 **/
int main() {
    Grand * pg;
    Superb * ps;
    std::srand(std::time(0));
    for (int i = 0; i < 5; ++i) {
        pg = GetOne();
        if (pg != nullptr)
            pg->Speak();
        if (ps = dynamic_cast<Superb *> (pg))
            ps->Say();
        delete pg;
    }
    return 0;
}
```

> 即使编译器支持 RTTI，但在默认情况下，它也可能会关闭该特性。如果该特性被关闭，程序可能仍能通过编译，但将在运行阶段报错。在这种情况下，您应查看文档或菜单选项。

在上面的程序中还说明了重要的一点：**应尽可能使用虚函数，而只在必要时使用 RTTI**。

```cpp
// Output
I am a Grand class.
I am a Magnificent class.
I hold the character P and the integer 20009!
I am a Superb class.
I hold the Superb value of 28534!.
I am a Magnificent class.
I hold the character G and the integer 28736!
I am a Grand class.
```

输出正如您所看到的，只为 Superb 和 Magnificent 类调用了 Say() 方法。

<font color="red">dynamic_cast 运算符也可以用于引用</font>，其用法稍微有点不同：没有与空指针对应的引用值，因此无法使用特殊的引用值来指示失败。当请求不正确时，dynamic_cast 将引发类型为 bad_cast 的异常，这种异常从 exception 类派生来的，在 typeinfo 头文件中定义的。因此，可以像下面这样使用该运算符：

```cpp
#include <typeinfo>
...
Grand & rg = GetOne(); // 此处的 GetOne() 是引用版的
try {
    Superb & rs = dynamic_cast<Superb &> (rg);
    ...
} catch (std::bad_cast & e) {
    ...
}
```

#### typeid 运算符和 type_info 类

typeid 运算符使得能够确定两个对象是否为同一种类型。它与 sizeof 有点类似，可以接受两种参数：
- 类名；
- 结果为对象的表达式。

typeid 运算符返回一个对 type_info 对象的引用，其中 type_info 是在头文件 typeinfo 中定义的一个类：

```cpp
class type_info {
public:
    virtual ~type_info();

    const char* name() const noexcept { return __name[0] == '*' ? __name + 1 : __name; }
    bool before(const type_info& __arg) const noexcept;
    bool operator==(const type_info& __arg) const noexcept;
    bool operator!=(const type_info& __arg) const noexcept { return !operator==(__arg); }
    size_t hash_code() const noexcept;
    virtual bool __is_pointer_p() const;
    virtual bool __is_function_p() const;
    virtual bool __do_catch(const type_info *__thr_type, void **__thr_obj,
			    unsigned __outer) const;
    virtual bool __do_upcast(const __cxxabiv1::__class_type_info *__target,
			     void **__obj_ptr) const;

protected:
    const char *__name;
    explicit type_info(const char *__n): __name(__n) { }

private:
    type_info& operator=(const type_info&);
    type_info(const type_info&);
};
```

type_info 类重载了 == 和 != 运算符，以便可以使用这些运算符来对类型进行比较。例如，如果 pg 指向的是一个 Magnificent 对象，则下述表达式的结果为 bool 值 true，否则为 false：

```cpp
typeid(Magnificent) == typeid(*pg)
```

如果 pg 是一个空指针，程序将引发 bad_typeid 异常。该异常类型是从 exception 类派生而来，是在头文件 typeinfo 中声明的。

type_info 类的实现因厂商而异，但包含一个 name() 成员，该函数返回一个随实现而异的字符串：通常(但并非一定)是类的名称。例如，下面的语句显示指针 pg 指向的对象所示的类定义的字符串：

```cpp
cout << typeid(*pg).name() << endl;
```

对前面的程序进行一些修改，以使用 typeid 运算符与 name() 这个 type_info 类的成员函数:
> 注意：typeid 运算符和 name() 成员函数都适用于 dynamic_cast 和虚函数不能处理的情况。详见下节误用 RTTI 的例子。

```cpp
#include <typeinfo>
int main() {
    Grand * pg;
    Superb * ps;
    std::srand(std::time(0));
    for (int i = 0; i < 5; ++i) {
        pg = GetOne();
        if (pg != nullptr) {
            std::cout << "Now type is " << typeid(*pg).name() << ".\n";
            pg->Speak();
        }
        if (ps = dynamic_cast<Superb *> (pg))
            ps->Say();
        if (typeid(Magnificent) == typeid(*pg))
            std::cout << "This is a Magnificent.\n";
        delete pg;
    }
    return 0;
}
```

```
// 输出：
Now type is 11Magnificent.
I am a Magnificent class.
I hold the character S and the integer 15800!
This is a Magnificent.
Now type is 6Superb.
I am a Superb class.
I hold the Superb value of 32641!.
Now type is 6Superb.
I am a Superb class.
I hold the Superb value of 15709!.
Now type is 11Magnificent.
I am a Magnificent class.
I hold the character K and the integer 2324!
This is a Magnificent.
Now type is 5Grand.
I am a Grand class.
```

> 在《C++ Primer Plus》中的程序输出是 Grand，而我这里输出的是 5Grand，这是由于编译器的不同导致的。

#### 误用 RTTI 的例子

C++界有很多人都对 RTTI 口诛笔伐，他们认为 RTTI 是多余的，是导致程序效率低下和糟糕编程方式的罪魁祸首。这里不讨论对 RTTI 的争论，而只介绍一下应避免的编程方式。

下面是上个程序中的一段核心代码：

```cpp
Grand * pg;
Superb * ps;
std::srand(std::time(0));
for (int i = 0; i < 5; ++i) {
    pg = GetOne();
    if (pg != nullptr)
        pg->Speak();
    if (ps = dynamic_cast<Superb *> (pg))
        ps->Say();
    delete pg;
}
```

它利用了 dynamic_cast 和虚函数的特性，如果放弃 dynamic_cast 与虚函数，转而使用 typeid 来替代它们，那么可以将上述代码重新编写为：

```cpp
/**
 * RTTI 误用的例子：typeid 应该用于 dynamic_cast 和虚函数无法使用的场景，而不是替代 dynamic_cast，下面演示下不推荐的用法
 **/
int main() {
    Grand * pg;
    Superb * ps;
    Magnificent * pm;
    for (int i = 0; i < 5; ++i) {
        pg = GetOne();
        if (typeid(Magnificent) == typeid(*pg)) {
            pm = (Magnificent *) pg;
            pm->Speak();
            pm->Say();
        } else if (typeid(Superb) == typeid(*pg)) {
            ps = (Superb *) pg;
            ps->Speak();
            ps->Say();
        } else {
            pg->Speak();
        }
        delete pg;
    }
    return 0;
}
```

上述代码不仅比原来的更长、更难看，而且显式地指定各个类存在严重的缺陷。例如，对于该程序，如果有新的需求要求新增一个从 Magnificent 类派生的 Insufferable 类，而且 Insufferable 类也重新定义了 Speak() 和 Say()。那么使用 typeid 的方式来显式地测试每个类时，就必须添加一个 else if 来处理 Insufferable。

> 提示：如果发现在扩展的 if else 语句系列中使用了 typeid，则应考虑是否应该使用虚函数和 dynamic_cast。
> 另外，使用 if else + typeid 时，不需要像 catch 块那样考虑继承结构，因此即使先判断 Grand 也是可以的。

## 类型转换运算符

C语言的类型转换，是将类型名作为强制类型转换运算符：

```cpp
int i1 = 10;
double d1 = 1.11;
int * pi1 = &i1;
double * pd1 = &d1;

double d2 = i1; // 低精度转换为高精度，可以隐式转换
int i2 = (int) d1; // 高精度强制转换为低精度，需显式转换
int * pi2 = (int *) pd1; // valid
double * pd2 = (double *) pi1; // valid
```

在C++的创始人看来，C语言的类型转换运算符都太过松散。例如，请看下面的代码：

```cpp
double d[20] = { 2.5, 3.5, 20.2};
char * pch = (char *) d;
```

上面的类型转换有意义吗？除非某些特别的要求，否则将 double 数组的地址转换为字符指针并没有什么意义。上面的类型转换在C语言中是被允许的，C++ 为保持兼容而予以保留。

但C++的创始人认为对于这种松散的情况，应该更严格地限制允许的类型转换，并添加了 4 个类型转换运算符，使转换过程更规范：

- dynamic_cast
- const_cast
- static_cast
- reinterpret_cast

可以根据目的选择一个合适的运算符，而不是使用通用的类型转换。特别是强制类型转换是有一定风险的，例如，精度损失、常量指针修改为非常量指针导致原始常量被破坏等。C++引入新的类型转换机制，可以在程序中指出进行类型转换的原因，并让编译器能够检查程序的行为是否与设计者的想法温和。另一个好处是能让程序员更容易看到程序中哪里发生了类型转换。使用C语言风格的类型转换会很难查找哪里发生了类型转换，而使用C++的新机制只需要搜索 _cast 即可。

### dynamic_cast

dynamic_cast 运算符已经在前面的 RTTI 处介绍过了。这里简单复习下，假设有 Big 和 Small 两个类，而 pb 和 ps 的类型分别是 Big* 和 Small*，则仅当 Small 是 Big 的直接或间接基类时，下面的语句才将一个 Small 指针赋给 ps，否则该语句将空指针赋给 ps：

```cpp
ps = dynamic_cast<Small *> (*pb);
```

通常 dynamic_casat 运算符的语法如下：

```cpp
dynamic_cast<type_name> (expression)
```

**该运算符的用途是，使得能够在类层次结构中进行安全地向上转换，而不允许其他转换**。


### const_cast

const_cast 运算符用于执行只有一种用途的类型转换，即改变值为 const 或 volatile，其语法与 dynamic_cast 运算符相同：

```cpp
const_cast<type_name> (expression)
```

**除了 const 或 volatile 特征可以不同外，type_name 和 expression 的类型必须相同**。假设 Big 和 Small 是两个类：

```cpp
Big big;
const Big * pb = &big;

High * pb = const_cast<High *> (pb); // valid
const Small * ps = const_cast<Small *> (pb); // invalid
```

第一个类型转换使得 \*pb 成为一个可以修改 big 对象的指针，它删除了 const 标签。第二个类型转换是非法的，因为它同时尝试将类型从 const Big \* 类型修改为 const Small \* 类型。

提供该运算符的原因是，有时候可能需要这样一个值：它在大多数时候是常量，而有时又是可以修改的。在这种情况下，可以将这个值声明为 const，并在需要修改它的时候，使用 const_cast。这也可以通过通用类型转换来实现，但通用类型转换也可能会同时修改类型：

```cpp
Big big;
const Big * pb = &big;

High * pb = (High *) pb; // valid
Small * ps = (Small *) pb; // valid
```

这样程序员就可能在编程中无意间同时改变类型与常量特征，因此使用 const_cast 运算符更安全。

当然 const_cast 并不是万能的。它可以修改指向一个值的指针，但修改 const 值的结果是不确定的。

```cpp
/**
 * 修改常量指针所指向的常量值
 **/
void change(const int * pInt, int n) {
    int * p = const_cast<int *> (pInt);
    *p += n;
}
/**
 * const_cast 运算符的测试
 **/
int main() {
    int i1 = 3333;
    const int i2 = 2000;

    std::cout << "i1, i2: " << i1 << ", " << i2 << std::endl;

    change(&i1, -100);
    change(&i2, -100);

    std::cout << "i1, i2: " << i1 << ", " << i2 << std::endl;
    return 0;
}
```

const_cast 运算符可以删除 const int * pInt 中的 const，使得编译器允许 change() 中的语句：

```cpp
*p += n;
```

但由于 main() 中的 i2 被声明为 const，因此编译器可能禁止修改它，如下面的输出结果所示，即使调用了 change()，打印的 i2 值也没有发生变化：

```cpp
i1, i2: 3333, 2000
i1, i2: 3233, 2000
```

如上所示，调用 change() 之后，i1 的值发生了变化，但并没有修改 i2。在 change() 中，指针 pInt 被声明为 const int *，因此不能用来修改指向的 int。而指针 p 使用 const_cast 运算符删除了 const 特征，因此可以用来修改指向的值。但仅当指向的值不是 const 时才可行。因此，指针 p 可用于修改 i1，但不能用于修改 i2.

### static_cast

static_cast 运算符的语法与其他类型转换运算符相同：

```cpp
static_cast<type_name> (expression)
```

**仅当 type_name 可被隐式转换为 expression 所属的类型或 expression 可被隐式转换为 type_name 所属的类时，上述转换才合法，否则将出错**。

> static_cast 适用于“低风险”的类型转换。

假设 High 是 Low 的基类，而 Pond 时一个无关的类，则从 High 到 Low 的转换、从 Low 到 High 的转换都是合法的，而从 Low 到 Pond 的转换是不被允许的：

```cpp
class Low : public High {};
...
High bar;
Low blow;
...
High *ph = static_cast<High *> (&blow); // valid upcast
Low *pl = static_cast<Low *> (&bar); // valid downcast
Pond * pp = static_cast<Pond *> (&blow); // invalid, Pond unrelated
```

第一个转换是合法的，因为向上转换可以显示地进行。第二个转换是从基类指针到派生类指针，在不进行显示类型转换的情况下，将无法进行。但由于无需进行类型转换(转换1)，便可以进行另一个方向的类型转换，因此使用 static_cast 来进行向下转换是合法的。

同理，由于无需进行类型转换，枚举值就可以被转换为整型，所以可以用 static_cast 将整型转换为枚举值。同样地，可以用 static_cast 将 double 转为 int，将 float 转换为 long 以及其他个数值转换。

### reinterpret_cast

> reinterpret -> 重新诠释

reinterpret_cast 运算符用于天生危险的类型转换。它不允许删除 const, 但会执行其他令人生厌的操作。有时程序员必须做一些依赖于实现的、令人生厌的操作，使用 reinterpret_cast 运算符可以简化对这种行为的跟踪工作。该运算符的语法与另外三个相同：

```cpp
reinterpret_cast<type_name> (expression)
```

下面是一个使用示例：

```cpp
struct dat { 
    short a; 
    short b;
};
long value = 0x11223344;
dat * pd = reinterpret_cast<dat *> (&value);
cout << hex << pd->a; // display first 2 bytes of value
```

通常，这样的转换适用于依赖于实现的底层编程技术，是不可移植的。例如，不同系统在存储多字节整型时，可能以不同的顺序存储其中的字节。

然而，reinterpre_cast 运算符并不支持所有的类型转换。例如，可以将指针类型转换为足以存储指针表示的整型，但不能将指针转换为更小的整型或浮点型。另一个限制是，不能将函数指针转换为数据指针，反之亦然。

在C++中，普通类型转换也受到限制。基本上，可以执行其他类型转换可执行的操作，加上一些组合，如 static_cast 或 reinterpret_cast 后跟 const_cast，但不能执行其他转换。因此，下面的类型转换在C语言中是允许的，但在C++中通常不允许，因为对于大多数C++实现，char 类型都太小，不能存储指针：

```cpp
char ch = char (%d);
```

这些限制是合理的。

## 总结

RTTI(Runtime Type Indentify) 特性让程序能够检测对象的类型。能使用 dynamic_cast 时优先使用 dynamic_cast，只有在不能使用 dynamic_cast 时才考虑 typeid 运算符与 type_info 类对象的用法。

dynamic_cast 运算符用于将派生类指针转换为基类指针，其主要用途是确保能够安全地调用虚函数。如果该运算符的操作对象不能安全的转换(不是 type_name 类型或其直接或间接派生类)为 type_name，那么 dynamic_cast 将返回空指针(0)。

typeid 运算符返回一个 type_info 对象，它和 sizeof 类似，其操作对象可以是类对象或者类型。而 type_info 类重载了 == 与 !=，因此可以对两个 typeid 的返回值进行对比，以确定对象是否为特定的类型。返回的 type_info 对象可用于获得关于对象的信息，例如 name() 函数虽然依赖于库的实现，但一般都会返回一个关于类名称的字符串。

与继承自C语言的通用转换机制相比，dynamic_cast/static_cast/const_cast/reinterpret_cast 提供了更安全、更明确的类型转换。

- dynamic_cast 运算符用于将派生类指针(or 引用)安全地转换为基类指针(or 引用)，如果不能安全的进行转换，那么返回空指针。
- static_cast 运算符用于风险较低的转换，它要求要么待转换的类型可以隐式转换为目标类型，要么目标类型可以隐式转换为待转换类型。
- const_cast 运算符是四个运算符中唯一一个可以去除 const 或 volatile 的。
- reinterpret_cast 运算符可以对两个类型进行转换，它不会考虑安全性。