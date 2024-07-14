## C++11 新特性

### 复习前面介绍过的 C++ 新特性

#### 1. 新类型

C++11 新增了类型
- long long 和 unsigned long long，以支持 64 位(或更宽)的整型；
- char16_t 和 char32_t，以支持 16 位和 32 位的字符表示；
- 原始字符串。

> 原始字符串字面量是一种字符串表示方法，它允许你编写包含特殊字符的字符串，而无需使用转义字符。

在C++中，原始字符串字面量以`R"(`开始，以`)"`结束，并且不会对其中的任何字符进行处理，包括转义字符。

```cpp
// 普通字符串 "Hello, World."\M
std::string str1 = "\"Hello, World.\"\\M";
// 原始字符串
std::string str2 = R"("Hello, World."\M)";
```

原始字符串主要是避免了字符串中的转义字符，在包含多个转义字符的字符串中使用它更为方便。例如：正则表达式。

#### 2. 统一的初始化 —— 初始化列表

C++11 扩大了用大括号`{}`括起的列表(初始化列表)的使用范围，使其可以用于所有内置类型和用户自定义的类型(即结构和类对象)。
> 使用初始化列表时可以添加等号`=`，也可以不添加。

```cpp
int x = {5};
double y {2.55};
int z[5] {1, 2, 3, 4, 5};
```

初始化列表语法也可以用在 new 中：

```cpp
int * arr = new int [5] {1, 2, 3, 4, 5};
```

创建类对象时，使用初始化类别可以调用对应的构造函数：

```cpp
class Demo {
private:
    int x;
    double y;

public:
    Demo(int x1, double y1) : x(x1), y(y1) {}
};

int main() {
    Demo d1(3, 1.1);    // 直接调用构造函数
    Demo d2{2, 3.5};    // C++11 初始化列表，调用 Demo(int, double) 构造函数
    Demo d3 = {5, 6.5}; // C++11 初始化列表，调用 Demo(int, double) 构造函数
}
```

然而，如果类有将模板`std::initialzer_list`作为参数的构造函数，则只有该构造函数能够使用列表初始化形式。

**1.缩窄**：
列表初始化语法可以有效防止缩窄，即禁止将数值赋给无法存储它的数值变量。常规初始化允许程序员执行可能没有意义的操作：

```cpp
char c = 1.57; // double to char
```

然而，如果使用列表初始化语法，编译器将禁止进行这样的类型转换，即将值存储到比它更“窄”的变量中：

```cpp
char c = {1.57}; // double to char，编译器将报错
```

不过，列表初始化允许转为为更宽的类型。另外，只要值在较窄类型的取值范围内，将其转换为较窄类型也是允许的：

```cpp
char c1 {66}; // int to char，但 66 在 char 类型范围内，所以可以转换
double c2 {66}; // int to double，double 是更宽的类型，可以转换
```

**2.std::initializer_list**：
C++11 提供了模板类 initializer_lis，可将其用作构造函数的参数，这在 Unit 10 中简单介绍过。

如果类接受`initializer_list`作为参数的构造函数，则列表初始化语法就只能用于该构造函数。其中列表中的元素必须是同一种类型或可以转换为同一种类型。STL 容器提供了将`initializer_list`作为参数的构造函数：

```cpp
std::vector<int> arr1(10); // 声明了一个包含10个整型元素的 arr1，但没有初始化元素
std::vector<int> arr2{10}; // 声明了一个包含1个整型元素的 arr2，同时将该元素初始化为 10
std::vector<int> arr3{4, 6, 1}; // 声明了一个包含3个整型元素的 arr3，同时将它们初始化为 4，6，1
```

头文件`initializer_list`提供了对模板类`initializer_list`的支持。这个类包含成员函数 begin() 和 end()，可用于获得列表的范围。除用于构造函数之外，还可以将`initializer_list`用于常规函数的参数：

```cpp
double sum(std::initializer_list<double> il) {
    double sum = 0;
    for (auto t = il.begin(); t != il.end(); t++)
        sum += *t;
    return sum;
}

int main() {
    double total = sum({2.5, 3.3, 4.8}); // 10.6
}
```

#### 3. 声明

C++11 提供了多种简化声明的功能，特别是在使用模板时。

**1.auto**
以前，auto 关键字是一个存储类型说明符，C++11 将其用于实现自动类型推断。这要求声明变量时对其进行显式初始化，这样编译器能够将变量的类型设置为其初始值的类型。

auto 关键字常用于遍历 STL 容器。例如，假设 il 是一个`std::initializer_list<double>` 对象：

```cpp
for (std::initializer_list<double>::iterator temp = il.begin(); temp != il.end(); temp++)
// 可以被替换为下面的代码
for (auto temp = il.begin(); temp != il.end(); temp++)
```

**2.decltype**
关键字 decltype 用于将变量类型什么为表达式指定的类型。下面语句的含义是，让 z 的类型与 x+y 相同：

```cpp
decltype(x+y) z;
```

这在定义模板时特别有用，因为只有等模板被实例化时才能确定类型：

```cpp
template<typename T, typename U>
void func(T t, U u) {
    decltype (t*u) tu;
    // ...
}
```

其中 tu 的类型为表达式`t*u`的类型。

decltype 的工作原理比 auto 负责，根据使用的表达式，指定的类型可以是引用和 const：

```cpp
int i = 3;
int &j = i;
const int & k = j;
decltype(i) n1; // n1 type is int
decltype(j) n2; // n2 type is int &
decltype(k) n3; // n3 type is const int &
decltype(j+1) n4; // n4 type is int
```

> decltype 中的 declare v. 声明

decltype 常配合返回类型后置使用。

**3.返回类型后置**
C++11 新增了一种函数声明语法：在函数名和参数列表后面(而不是前面)指定返回类型：

```cpp
double f1(double, int); // 传统语法
auto f2(double, int) -> double; // 新语法，返回类型后置
```

就常规函数的可读性而言，这种新语法好像是种倒退，但它能够让您通过和 decltype 搭配使用来指定模板函数的返回值类型：

```cpp
template<typename T, typename U>
auto func(T t, U u) -> decltype(t*u) {
    decltype (t*u) tu;
    // ...
}
```

这里解决的问题是，在编译器遇到 func 的参数列表之前，t 和 u 还不在作用域内，因此必须在参数列表后使用 decltype。这种新语法使得能够这样做。

> 另外，返回类型后置和 decltype 也常常搭配 lambda 表达式

**4.模板别名：using=**
对于冗长或复杂的标识符，如果能够创建其别名将很方便。以前，C++为此提供了 typedef：

```cpp
typedef std::vector<std::string>::iterator it;
```

C++11 提供了另一种创建别名的语法：

```cpp
using it = std::vector<std::string>::iterator it;
```

它们的差别在于，新语法可以用于模板部分具体化，而 typedef 不能：

```cpp
template<typename T>
    using arr12 = std::array<T, 12>;
```

上述语句具体化模板`array<T, int>`，这样可以用替换声明：

```cpp
std::array<double, 12> a1;
std::array<int, 12> a2;

// 替换为：
arr12<double> arr1;
arr12<int> arr2;
```

**5.nullptr**
空指针是不会指向有效数据的指针。以前，C++在源代码中使用0表示这种指针，但内部表示可能不同。这带来了一些问题，因为这使得0既可以表示指针常量，又可以表示整型常量。

C++11新增了 nullptr 关键字，用于表示空指针。它是指针类型，且不能转换为整型类型。为向后兼容，C++11 仍允许使用 0 来表示空指针，因此表达式`nullptr == 0`为 true，但使用 nullptr 而不是 0 提供了更高的类型安全。

#### 4. 智能指针

如果在程序中使用 new 从堆(自由存储区)分配内存，等到不再需要时，应使用 delete 将其释放。C++引入智能指针 auto_ptr，以帮助自动完成这个过程。
随后的编程体验(尤其是使用 STL 时)表明，需要有更精致的机制。基于程序员的编程体验和 BOOST 库提供的解决方案，C++11 摒弃了 auto_ptr，并新增了三种智能指针：unique_ptr、shared_ptr 和 weak_ptr。

所有新增的智能指针都能与 STL 容器和移动语义协同工作。

#### 5. 异常规范方面的修改

以前，C++提供了一种语法，可以用于指出函数可能引发哪些异常：

```cpp
void f1(int) throw(bad_err); // 可能会抛出一个 bad_err 的异常
void f2(double) throw(); // 不会抛出异常
```

与 auto_ptr 一样，C++编程社区的集体经验表明，异常规范的效果没有预期的好。因此，C++11 摒弃了异常规范。然而，标准委员会认为，指出函数不会引发异常有一定的价值，他们为此添加了 noexcept 关键字：

```cpp
void f3(string) noexcept; // 不会抛出异常
```

> 虽然 `throw()` 和 `noexcept` 都表示函数不会抛出异常，但 `throw()` 是被摒弃的异常规范，因此更推荐使用 noexcept 作为不会抛出异常的指示。

#### 6. 作用域内枚举

传统的C++枚举提供了一种创建名称常量的方式，但其类型检查相当低级。另外，枚举名的作用域为枚举定义所属的作用域，这意味着如果在同一个作用域内定义两个枚举，它们的枚举成员不能同名。
最后，枚举可能不是可完全移植的，因为不同的实现可能选择不同的底层类型。为解决这些问题，C++11 新增了一种枚举。这种枚举使用 class 或 struct 定义：

```cpp
enum e1 { red, yellow, blue }; // 传统枚举
class enum e2 { yes, no, green }; // 新枚举类型
struct enum e3 { monday, yes, may }; // 新枚举类型
```

新枚举要求进行显式限定，以免发生名称冲突。因此，引用特定枚举时，需要这样使用：`e2::yes`。

#### 7. 对类的修改

为简化和扩展类设计，C++11 做了多项改进。这包括允许构造函数被京城和彼此调用、更加的方法访问控制方式以及移动构造函数和移动赋值运算符。
这里先复习前面介绍过的显式转换运算符和类内成员初始化。

**1.显式转换运算符**
C++很早就支持对象自动转换，但随着编程经验的基类，程序员逐渐认识到，自动类型转换可能导致意外转换的问题。为解决这种问题，C++引入了 explicit，以禁止单参数构造函数导致的自动转换。

C++11 拓展了 explicit 的用法，使得可对转换函数做类似的处理：

```cpp
class Demo {
    explicit Demo(int);
    operator int() const;
    explicit operator double() const;
};
```

**2.类内成员初始化**
现在可以在类定义内初始化成员：

```cpp
class Demo {
private:
    int d1 = 10; // 初始化
    double d2 { 3.33 }; // 初始化
    char d3;
}
```

可使用等号或者大括号版本的初始化，但不能使用圆括号版本的初始化。

通过使用类内初始化，可避免在构造函数中编写重复的代码，从而降低程序员的工作量、厌倦情绪和出错的机会。

如果构造函数在成员初始化列表中提供了相应的值，这些默认值将被覆盖。

#### 8. 模板和 STL 方面修改

为改善模板和标准模板库的可用性，C++11做了多个改进。有些是库本身，有些与易用性相关。

**1.基于范围的 for 循环**
对于内置数组、包含方法 begin() 和 end() 的类和 STL 容器，基于范围的 for 循环可简化为它们编写循环的工作。这种循环对数组或容器中的每个元素执行指定操作：
```cpp
double arr[] = {2.3, 22.378, 6.93, 6.44};
for(double x : arr)
    std::cout << x std::endl;
```

一种更容易、更安全的方式是，使用 auto 来声明 x，这样编译器将根据 arr 中的信息来推断 x 的类型。

如果要在循环中修改数组或容器的每个元素，可使用引用类型：

```cpp
double arr[] = {2.3, 22.378, 6.93, 6.44};
for(auto & x : arr)
    x = x+2;
```

**2.新的 STL 容器**
C++11 新增了 STL 容器 forward_list、unordered_map、unordered_multimap、unordered_set 和 unordered_multiset。容器 forward_list 是一种单向链表，只能沿一个方向遍历；与双向链表的 list 容器相比，它更简单，在占用存储空间方面更经济。其他四种容器都是使用哈希表实现的。
C++11 还新增了模板 array。要实例化这种模板，可指定元素类型和固定的元素数：

```cpp
std::array<int, 12> arr;
```

这个模板类没有满足所有的常规模板需求。例如，它的长度固定，不能使用任何修改容器大小的方法，如 put_back()。但 array 确实有方法 begin() 和 end()，这让您能够对 array 对象使用众多基于范围的 STL 算法。

**3.新的 STL 方法**
C++11 新增了 STL 方法 cbegin() 和 cend()。与 begin() 和 end() 一样，这些新方法也返回一个迭代器，指向容器的第一个元素和最后一个元素的后面，因此可用于指定包含全部元素的区间。另外，这些新方法将元素视为 const。与此类似，crbgin() 和 credn() 是 rbegin() 和 rend() 的 const 版本。

**4.valarray 升级**
模板 valarray 是独立于 STL 开发的，其最初设计导致无法将基于范围的 STL 算法用于 valarray 对象。C++11 添加了两个函数(begin 和 end)，它们都接受 valarray 作为参数，并返回迭代器，这些迭代器分别指向 valarray 对象的第一个元素和最后一个元素后面。这让您能够将基于范围的 STL 算法用于 valarray。

**5.摒弃 export**
C++98 新增了 export 关键字，旨在提供一种途径，让程序能够将模板定义放在接口文件和实现文件中，其中前者包含原型和模板声明，而后者包含模板函数和方法的定义。但实践证明这不现实，因此 C++11 终止了这种用法，但仍保留关键字 export。

**6.尖括号**
为避免与运算符`>>`混淆，C++要求在声明嵌套模板时使用空格将尖括号分开。现在 C++11 不再这样要求：
```cpp
std::vector<std::list<int> > v1; // 传统
std::vector<std::list<int>> v2; // C++11
```

### 右值引用和移动语义

#### 右值引用

传统的C++引用(现在被称为左值引用)使得标识符关联到左值。
**左值**：左值是一个表示数据的表达式，如变量名或解除引用的指针，程序可获取其地址。
最初，左值可出现在赋值语句的左边，但修饰符 const 的出现使得可以声明这样的标识符，即不能给它赋值，但可获得其地址：

```cpp
int n;
int * p = new int;
const int b = 100; // 不能修改 b 的值，但可以获取 b 的地址
// 左值引用
int & rn = n;
int & rp = *p;
const int & rb = b;
```

C++11 新增了右值引用，右值引用使用`&&`表示。—— 右值引用的使用方法
**右值**：可出现在赋值表达式右边，但不能对其应用地址运算符的值。右值包含字面常量(C-风格字符串除外，因为它表示地址)、诸如`x+y`等表达式以及返回值的函数(要求该函数返回的不是引用)：

```cpp
int x = 100;
int y = 250;
int && r1 = x+y;
int && r2 = 99;
double && r3 = std::sqrt(4.4);
```

注意，r1 关联到的是 x+y 的计算结果。也就是说，r1 关联的是 350，即使之后修改了 x 或 y，也不会影响到 r1。

有趣的是，将右值关联到右值引用导致该改右值被存储到特定为止，且可以获取该位置的地址。也就是说，虽然不能将运算符&用于 99，但可将其用于 r1.通过将数据与特定的地址关联，使得可以通过右值引用来访问该数据。

```cpp
std::cout << "r1 value and address: " << r1 << ", " << &r1 << std::endl;
```

为什么要引入右值引用？
A：引入右值引用的主要目的之一是实现移动语义。

C++11 支持移动语义，这就提出了一系列问题：
- 什么是移动语义？
- C++11 如何支持它？
- 为何需要移动语义？

下面将讨论它们。

#### 为什么需要移动语义？

**移动语义**：它允许以非常低的代价将资源的拥有权从一个对象转移到另一个对象，这样可以避免不必要的对象复制操作，从而提高程序的效率。

想要理解为何需要移动语义，需要回顾下复制的过程。假设有一个包含 10000 个 string 对象的数组 vstr，其中每个 string 对象有 1000 个字符，现在要将它复制到 vstr_copy：

```cpp
vector<string> vstr; 
vector<string> vstr_copy(v_str); // 复制构造函数
```

vector 和 string 都是用动态内存分配，为初始化对象 vstr，复制构造函数`vector<string>`将使用 new 给 10000 个 string 对象分配内存，而每个 string 对象又会调用 string 的复制构造函数，该构造函数使用 new 为 1000 个字符分配内存。接下来，将全部的 10000000 个字符从 vstr 的内存中复制到 vstr_copy 控制的内存中。这里的工作量很大，但只要妥当就行。

但这确实妥当吗？有时候答案是否定的，这可能导致大量无用功：

```cpp
vector<string> upper_string(const vector<string> & vstr) {
    std::vector<std::string> temp(vstr);
    // 将每个小写字符转换为大写字符
    for (auto & x:temp) {
        std::transform(x.begin(), x.end(), x.begin(), [](char c) { return std::toupper(c); } );
    }
    return temp;
}

int main() {
    using namespace std;
    vector<string> vstr; // 10000 个 string 对象，每个 string 对象有 1000 个字符
    vector<string> vstr_copy1(vstr); // #1
    vector<string> vstr_copy2(upper_string(vstr)); // #2
}
```

#1 和 #2 都使用现有对象 vstr 初始化一个`vector<string>`对象。
- #1 将使用 new 申请 10000*1000 个存储 char 的内存，并从 vstr 中依次将这些字符复制到 vstr_copy1 控制的内存中。
- #2 
  - 首先，upper_string() 用申请一个 10000*1000 个存储 char 的内存，这些内存由临时对象 temp 管理，然后将参数 vstr 的字符依次复制到 temp 中。
  - 其次，upper_string() 在将参数 vstr 的字符复制到 temp 中之后，还对其内容做了一些修改：按照 lambda 表达式规定的操作(将小写字符修改为大写字符)修改 temp 中的字符。
  - 最后，upper_string() 将临时对象 temp 的内容复制到 vstr_copy2 中，而 vstr_copy2 同样申请了一块 10000*1000 个 char 的内存。
> lambda 表达式后面会对其进行介绍，可以视为匿名函数。

这里的要点是，程序做了大量无用功。考虑到临时对象 temp 在 upper_string() 函数运行完成后会被删除，那么如果能够让 temp 对数据的所有权直接转让给 vstr_copy2 对象不是更好吗？这样就可以减少 vstr_copy2 申请 `10000*1000*sizeof(char)` byte 内存以及删除 temp 控制的内存的工作量了。也就是说，不是将这`10000*1000`个字符复制到新的地方，再删除原来的字符，而是将字符留在原来的地方，只是修改记录，将控制这块内存的对象从 temp 修改为 vstr_copy2。**这种方法就被成为移动语义**。

> 与移动语义字面意思有点悖论的是，虽然它带了移动二字，但移动语义实际上是避免了移动原始数据，而只是修改了记录。
> 应理解移动的不是数据，而是将数据的控制权从一个对象移动到另一个对象。

#### 如何实现移动语义

了解了移动语义的好处，现在需要考虑如何实现移动语义。即需要采用什么方式，让编译器知道什么时候需要复制，而什么时候需要移动。这就是右值引用发挥作用的地方了。

复制操作存在于复制构造函数和赋值运算符，这里先说构造函数。下面定义两个构造函数，一个是常规的复制构造函数，它使用 const 左值引用(`&`)作为参数，这个引用关联到左值实参；另一个是移动构造函数，它使用右值引用(`&&`)作为参数，该引用关联到右值实参。复制构造函数执行深复制，而移动构造函数只调整记录。由于在将所有权转移给新对象的过程中，移动构造函数可能会修改实参，所以右值引用不应是 const。用法示例：

```cpp
class Demo {
private:
    static int ct;
    char * pc; // 字符指针
    int n;
public:
    Demo() = default;
    Demo(const Demo & d); // 复制构造函数
    Demo(Demo && d); // 移动构造函数
    Demo operator+(const Demo & d) const;
    ~Demo();
};

// Implement
int Demo::ct = 0;

// 复制构造函数
Demo::Demo(const Demo & d) {
    ct++;
    n = d.n;
    pc = new int[n];
    for (int i = 0; i < n; i++)
        pc[i] = d.pc[i];
}

// 移动构造函数
Demo::Demo(Demo && d) {
    ct++;
    n = d.n;
    pc = d.pc;
    d.pc = nullptr;
    d.n = 0;
}

Demo::~Demo() {
    ct--;
    delete [] pc;
}

int main() {
    Demo d;
    Demo d1 = d; // 调用复制构造函数
    Demo d2(d+d1); // 调用移动构造函数
}
```

在移动构造函数的实现中，它让 pc 指向现有数据，以获取这些数据的所有权。此时 pc 和 d.pc 指向相同的数据，调用析构函数时这会带来问题，因为程序不能对同一个地址调用`delete []`两次。为避免这种问题，需要将 d.pc 指向空指针，因为对空指针执行`delete []`没问题。这种夺取所有权的方式常被称为窃取(pilfering)。上面的代码还将原始对象的元素数重置为零，不过这并不是必不可少的。

`Demo d2(d+d1);` 表达式 d+d1 调用`Demo::oprator+()`，而右值引用 d 将关联到该方法返回的临时对象。

#### 移动构造函数

虽然使用右值引用可以支持移动语义，但要让移动语义发生，需要两个步骤：
- 首先，右值引用让编译器知道何时可以使用移动语义；
- 其次，编写移动构造函数，为移动语义提供所需的行为。

总之，通过提供一个使用左值引用的构造函数和一个使用右值引用的构造函数，将初始化分成了两组：
- 使用左值引用初始化对象时，将调用复制构造函数；
- 使用右值引用初始化对象时，将调用移动构造函数。

程序员可以根据需要赋予这些构造函数不同的行为。

#### 赋值运算符

适用于构造函数的移动语义也适用于赋值运算符。例如：

```cpp
// 赋值运算符 —— 复制
Demo & Demo::operator=(const Demo & d) { 
    if (this == &d)
        return *this;

    delete [] pc;
    n = d.n;
    pc = new char [n];
    for(int i = 0; i < n; i++)
        pc[i] = d.pc[i];
    return *this;
}

// 赋值运算符 —— 移动
Demo & Demo::operator=(Demo && d) {
    if(this == &d)
        return *this;

    delete [] pc;
    n = d.n;
    pc = d.pc;
    d.pc = nullptr;
    d.n = 0;
    return *this;
}
```

上述复制赋值运算符采用常规模式，而移动赋值运算符删除了目标对象中的原始数据，然后将源对象的所有权转让给目标对象。不能让多个指针指向相同的数据，因此上述代码将源对象中的指针设置为空指针。
同样，移动赋值运算符的参数也不能是 const 引用，因为这个方法修改了源对象。

#### 强制移动

移动构造函数和移动赋值运算符使用右值。那如果想要让它们使用左值，该如何办呢？
- Method 1: 可以使用运算符`static_cast<>`将对象的类型强制转换为`Demo &&`；
- Method 2: 使用头文件`utility`中声明的函数`std::move()`。

```cpp
#include <utility>
// ...
Demo d1;

Demo d2 = d1 + d1; // 移动构造函数

Demo d3, d4;
d3 = d1 + d2; // 移动赋值运算符
d4 = d1; // 复制赋值运算符

d4 = static_cast<Demo &&>(d1);
d4 = std::move(d1); // 强制移动
```

需要注意的是，函数`std::move()`并非一定会导致移动操作。例如，假设 DemoA 是一个包含私有数据的类。

```cpp
DemoA da1;
//...
DemoA da2;
da2 = std::move(da1);
```

如果为 DemoA 定义了移动赋值运算符，那么上面的语句将调用移动赋值运算符。否则，将使用复制赋值运算符。如果也没有定义复制赋值运算符，那么就不允许上述赋值。

对于大多数程序员来说，右值引用带来的主要好处并非是让他们能够编写使用右值引用的代码，而是能够使用那些利用右值引用实现移动语义的库代码。例如，STL 类现在都有复制构造函数、移动构造函数、复制赋值运算符和移动赋值运算符。


### 新的类功能

除了前面复习的显式转换运算符、类内成员初始化之外，C++11 还新增了其他几个类功能。

#### 特殊的成员函数

在原有的特殊成员函数基础上，C++11 新增了两个：
- 默认构造函数
- 复制构造函数
- 析构函数
- 复制赋值运算符重载
- 移动构造函数(new)
- 移动赋值运算符(new)

默认构造函数：在没有提供任何参数的情况下，将调用默认构造函数。如果程序员没有给类定义任何构造函数，那么编译器将提供一个默认构造函数。这个版本的默认构造函数被称为默认的默认构造函数。对于内置类型的成员，默认构造函数不对其进行初始化；对于属于类对象的成员，则调用其默认构造函数。

如果您没有提供复制构造函数，而代码又需要使用它，编译器将提供一个默认的复制构造函数；如果您没有提供移动构造函数，而代码又需要使用它，编译器将提供一个默认的移动构造函数。在类似的情况下，编译器还将提供默认的复制赋值运算符和默认的移动赋值运算符。

最后，如果没有提供析构函数，编译器将提供一个。

对于前面描述的情况，也有一些例外：
- 如果您提供了析构函数、复制构造函数或复制赋值运算符，编译器将不会自动提供移动构造函数或移动赋值运算符；
- 如果您提供了移动构造函数或移动赋值运算符，编译器将不会自动提供复制构造函数和复制赋值运算符。

另外，默认的移动构造函数和移动赋值运算符的工作方式和复制版本类似：对于内置类型，它执行逐成员初始化并复制；对于类对象成员，将使用相应类的构造函数和赋值运算符，就想参数为右值一样。如果定义了移动构造函数和移动赋值运算符，将调用它们，否则将调用复制构造函数和复制赋值运算符。

#### 默认的方法和禁用的方法

C++11 引入了 default 和 delete 关键字让您能够更好地控制要使用的方法。
- default 关键字指明使用该方法的默认版本。例如，您提供了移动构造函数，因此编译器不会自动创建默认的默认构造函数、复制构造函数、复制赋值运算符，在这种情况，可以使用 default 显式地声明这些方法的默认版本。
- delete 关键字指明禁止编译器使用特定方法。例如，要禁止复制对象，可禁用复制构造函数和复制赋值运算符。

```cpp
class Demo {
public:
    Demo(Demo && d); // 移动构造函数
    Demo() = default; // 默认构造函数
    Demo(const Demo &) = delete; // 禁止复制构造函数
    Demo & operator=(const Demo &) = default; // 默认复制赋值运算符
};
```

之前曾经说过，要禁止复制，可将复制构造函数和赋值运算符放在类定义的 private 部分，但使用 delete 关键字也能达到这个目的，且更不容易犯错、更容易理解。

Q: 如果在启用

default 关键字只能用于 6 个特殊成员函数，但 delete 可用于任何成员函数。delete 的一种可能用法是禁止特定的转换函数。例如：

```cpp
class Demo {
public:
    void f(double);
    void f(int) = delete;
};

int main() {
    Demo d;
    d.f(1);
}
```

如果没有`void f(int) = delete;`，那么`1`会被提升为`1.0`，进而执行方法 f()。但有了`void f(int) = delete;`之后，`d.f(1)`与原型`void f(int)`匹配。编译器检测到这一点以及`f(int)`被禁用后，将这种调用视为编译错误。这说明了禁用函数的重要一点：它们只用于查找匹配函数，使用它们将导致编译错误。

#### 委托构造函数

如果给类提供了多个构造函数，您可能会重复编写某些相同的代码。也就是说，有些构造函数可能需要包含其他构造函数中已有的代码。。

**委托**：C++11 允许您在一个构造函数的定义中使用一个构造函数。这被称为委托，因为构造函数暂时将创建对象的工作委托给另一个构造函数。

**如何使用委托**？
- 委托使用成员初始化列表语法的变种

示例：

```cpp
class Demo {
private:
    int i;
    double j;
    string str;
public:
    Demo();
    Demo(int, double, string);
};

Demo::Demo(int ii, double jj, string s) : i(ii), j(jj), str(s) {}

Demo::Demo() : Demo(0, 0.1, " ") {}
```

#### 继承构造函数

为进一步简化编码工作，C++11 提供了一种让派生类能够继承基类构造函数的机制。

首先，回顾下 C++98 中提供的一种让名称空间中函数可用的语法：`using name_space::function;`

```cpp
namespace NameA {
    int fn(int) {...}
    int fn(double) {...}
    int fn(string) {...}
}
using NameA::fn;
```

这样函数 fn 的所有重载版本都可用。**这种方法也可以让基类的所有非特殊成员函数对派生类可用**。

```cpp
class C1 {
public:
    int fn(int);
    int fn(double);
    void fn(string);
};

class C2 : public C1 {
public:
    using C1::fn;
    int fn(double);
}
// 省略C1和C2成员函数的实现...

int main() {
    C2 c2;
    int j = c2.fn(3); // C1 的 fn(int)
    int k = c2.fn(2.5); // C2 的 fn(double)
}
```

上述代码，在 C2 中的 using 声明让 C2 对象能够使用 C1 的三个 fn() 方法，但对于`fn(double)`将选择使用 C2 中定义的，而不是 C1 的定义。

继承构造函数：**C++11 将这种方法用于构造函数，这让派生类继承基类的所有构造函数**(默认构造函数、复制构造函数、移动构造函数除外)，但不会使用与派生类构造函数特征标匹配的构造函数：

```cpp
class Base {
    int j;
    double k;
public:
    Base() : j(0), k(0.1) {}
    Base(int jj) : j(jj), k(10.1) {}
    Base(int jj, double kk) : j(jj), k(kk) {} 
};

class Inherited : public Base {
    char c;
    using Base::Base; // 可以使用基类的构造函数
    Inherited() : c('H') {} // 自己的默认构造函数
    Inherited(int jj) : c('J'), Base(jj, 3.3*jj) {}
    Inherited(double kk) : c('K'), Base(kk) {}
};

int main() {
    Inherited h1; // 使用 Inherited 的默认构造函数
    Inherited h2(222); // 使用 Inherited 的构造函数 Inhrited(int) 而不是基类的
    Inherited h3(3, 2.2); // 会用基类 Base 的 Inherited(int, double) 构造函数
}
```

由于 Inherited 没有构造函数`Inherited(int, double)`，所以创建 h3 对象时，将使用从 Base 继承来的构造函数。需要注意，继承来的基类构造函数只初始化基类成员，如果还要初始化派生类成员，则应该使用成员列表初始化语法 `Inherited(int jj) : c('J'), Base(jj, 3.3*jj) {}`

#### 管理虚方法：override 和 final

虚方法对实现多态类层次结构很重要，让基类引用或指针能够根据指向的对象类型调用相应的方法，但虚方法也带来了一些编程陷阱。例如，假设基类声明了一个虚方法，而您决定在派生类中提供不同的版本，这将覆盖旧版本，如果特征标不匹配，这将隐藏而不是覆盖：

```cpp
class Base {
    int a;
public:
    Base(int i = 0) : a(i) {}
    virtual void f(const char ch) const { cout << a << " " << ch << endl; }
};

class Inherited : public Base {
public:
    Inherited(int i = 1) : Base(i) {}
    virtual void f(const char * ch) const { cout << a << ", " << ch << endl; }
};
```

由于 Inherited 类定义的是`f(const char *)`而不是`f(const char ch)`，所以 Inherited 对象将隐藏`f(char char)`，这导致程序不能使用类似于下面的代码：

```cpp
Inherited i(100);
i.f('a');
```

**override**：在 C++11 中，可以使用虚说明符 override 指出您要覆盖一个虚函数。即在继承类中显式声明某个函数是覆盖了基类的函数，编译器就会检查它们的特征标是否一致，如果不一致编译会器会视为错误。

**如果使用 override**？
A: 将其放在参数列表的后面，像 const 一样。

```cpp
class Inherited {
    virtual void f(const char c) const override {
        // ...
    }
};
```

**final**：说明符 final 解决了另一个问题，它禁止派生类覆盖特定的虚方法。

**如何使用 final**？
A: 将其放可在参数列表后面

```cpp
class Base {
    virtual void f(const char c) const final {
        // ...
    }
};
```

### Lambda 函数

术语 Lambda 函数，也称 Lambda 表达式，常简称 Lambda，它是一种匿名函数的表达。

#### 来源

名称 Lambda 是源自 Lambda 演算(一种定义和应用函数的数学系统)，Lambda 演算最初是作为研究数学函数的可计算性的工具，但随着其流行，逐渐成为函数式编程语言的理论基础。

非形式化的直观描述：在 λ 演算中，每个表达式都代表一个函数，这个函数有一个参数，并且会返回一个值。不论是参数和返回值，也都是一个单参的函数。可以这么说，λ 演算中只有一种“类型”，那就是这种单参函数。函数是通过 λ 表达式匿名地定义的，这个表达式说明了此函数将对其参数进行什么操作。—— 百度百科

例如，“加2”函数f(x)= x + 2可以用 lambda 演算表示为 λx.x + 2（或者 λy.y + 2，参数的取名无关紧要），而f(3)的值可以写作 (λx.x + 2) 3。函数的应用是左结合的：f x y =(f x) y。
考虑这么一个函数：它把一个函数作为参数，这个函数将被作用在3上：λf.f 3。如果把这个（用函数作参数的）函数作用于我们先前的“加2”函数上：(λf.f 3)(λx.x+2)，则明显地，下述三个表达式是等价的：
- (λf.f 3)(λx.x+2) 
- (λx.x + 2) 3
- 3 + 2

有两个参数的函数可以通过 lambda 演算这样表达：一个单一参数的函数，它的返回值又是一个单一参数的函数（参见柯里化）。
例如，函数f(x, y) = x - y 可以写作 λx.λy.x - y。下述三个表达式是等价的：
- (λx.λy.x - y) 7 2
- (λy.7 - y) 2
- 7 - 2

如果您看不懂上面的描述，也没关系。只需要了解，Lambda 演算将函数通过 Lambda 表达式匿名地定义出来，Lambda 表达式是一种匿名函数。

即，**什么是 Lambda 表达式**？
A: Lambda 表达式是一种匿名函数，即无需给函数命名。

#### Lambda 语法

C++中 Lambda 函数的语法如下：

```cpp
[capture](parameters) -> return-type { body }
```

- `[]` 替代了函数名，这也是匿名的由来
- capture: 捕获外部变量的列表，这让 Lambda 可访问作用域内的任何变量。
  - 要捕获并使用的变量，可将其名称放到中括号内。
  - 如果只指定了变量名，如`[x]`，将按值访问变量。
  - 如果在变量名前加上&，如`[&x]`，将按引用访问变量，即能够修改它。
  - `[=]` 让您能够按值访问作用域内所有变量。
  - `[&]` 让您能够按引用访问作用域内所有变量。
  - 两种方式可以混合使用，如`[x, &y]`，`[=, &z]`。
- parameters: Lambda 函数的参数列表。
- return-type：Lambda 函数的返回值类型，这里使用的是返回类型后置的语法，见本章前面复习的 C++11 新特性。
  - 如果没有显式声明返回类型，相当于使用 decltype 根据返回值进行判断，如果 Lambda 不包含返回与，推断出的返回类型将为 void。
  - 仅当 Lambda 表达式完全由一条返回语句组成时，自动类型推断才管用；否则，需要使用返回类型后置语法。
- body：Lambda 函数的函数体。

下面是一些合法的 Lambda 表达式示例：

```cpp
// 判断参数 x 是否能被 3 整除的 Lambda 函数
[](int x) -> bool { return x % 3 == 0; } // 只有一条语句，所以可以省略返回类型后置

// 计算参数 x + y 的值，并返回的 Lambda 函数
[](int x, int y) -> int { return x + y; } // 只有一条语句，所以可以省略返回类型后置
[](int x, int y) { return x + y; } 

int count = 0;
// 如果参数 x 能被 3 整除，那么将作用域内的 count 变量 +1
[&count](int x) -> void { count += (x % 3 == 0); }
```

需要注意的是，Lambda 函数是匿名函数的声明，而不是函数调用。那么如何调用 Lambda 表达式呢？一种方法是使用包装器模板 function 来保存一个 Lambda 表达式：

```cpp
int main() {
    // 声明 Lambda 函数
    auto fadd = [](int x, int y)->int { return x+y; };
    // 调用 Lambda 函数
    int result = fadd(2, 3);
    std::cout << " Result: " << result << std::endl;
}

// 输出：
Result: 5
```

上述代码中，`auto fadd` 定义了一个 Lambda 表达式的对象 fadd 来关联 Lambda，然后使用这个对象来调用 Lambda。这种用法其实提供了一种在函数内部声明函数的方式，但这并不是 Lambda 函数常用的用法，它并没有体现匿名函数的优势，因为这个过程其实变相地为匿名函数命名为 fadd。

典型的 Lambda 是用于测试表达式或比较表达式，最好可以编写为一条返回语句，这样可以使得 Lambda 简洁、易于理解，且可以自动推断返回类型。最常见的情况是搭配 STL 算法使用。

#### 函数指针、函数符和 Lambda 函数

首先，我们先复习一下函数指针、函数符都是什么。

**函数指针**：它是一个指向函数的指针，可以用来调用函数，函数指针的声明方式如下：

```cpp
返回类型 (*函数指针名) (函数参数列表);
```

简单的记忆方法为，直接写出函数原型，并将函数名换成`(* 函数指针名)`就完成了一个函数指针的声明。

```cpp
int sum(int x, int y);

int main() {
    int (*pf)(int x, int y) = sum;
    int result = pf(2, 3);
}
```

**函数符**：函数符，也叫函数对象。它是指能够以函数方法与`()`结合的任意对象。这里的对象不仅限于类对象，而是指函数名、函数指针以及重载了`()`运算符的类对象(即重载了函数`operator()(参数列表)`的类)。

```cpp
class Demo {
public:
   double operator()(double x) { return 2.0*x; } 
};
```

在学习了 Lambda 函数之后，我们应该能够明白，函数符又多了一种表示 —— Lambda。

这里，为了方便描述，将函数符的表示缩小为重载了`()`运算符的类对象，而将函数对象保留原有定义。即函数指针、函数符和 Lambda 通称为函数对象。

**示例**：分别使用函数指针、函数符、Lambda 来为 STL 算法传递信息。假设您要生成一个随机整数列表，并判断其中多少个整数可被 3 整除，多少个整数可被 13 整除。

**通用部分**：生成随机列表。一种方案是使用`vector<int>`存储整型数字，并使用 STL 算法`generate()`往数组中填充随机数：

```cpp
// 生成 1000 个随机整数的列表
vector<int> vint(1000);
generate(vint.begin(), vint.end(), rand);
```

`generate()` 函数接受一个由前两个参数指定的区间，并将区间内的每个元素设置为第三个参数返回的值，而第三个参数接受的是一个没有任何参数的函数对象。在这个例子中，这个函数对象是一个指向标准函数`std::rand`的指针。

在判断哪些整数满足要求时使用的是`count_if()`算法，它和函数 generate() 一样，前两个参数是指定区间，而第三个参数应是一个返回 true 或者 false 的函数对象。conut_if() 会计算该区间内所有调用第三个参数后返回值为 true 的元素数目。

**使用函数指针实现**：定义两个函数，分别是判断整型是否可被 3 整除和是否可被 13 整除：

```cpp
bool f3 (int x) { return x % 3 == 0; }
bool f13(int x) { return x % 13 == 0; }
```

```cpp
int count3 = 0;
int count13 = 0;
// 函数指针版实现
count3 = count_if(vint.begin(), vint.end(), f3);
count13 = count_if(vint.begin(), vint.end(), f13);
cout << "count3: " << count3 << ", count13: " << count13 << endl;
```

**使用函数符实现**：前面说过这里将函数符缩小范围为重载了`operator()()`的类对象。就这个例子而言，函数符的优点之一是，可以使用一个类声明来完成这两项计数任务：

```cpp
int count3 = 0;
int count13 = 0;
// 函数符版实现
/**
* 重载 operator()() 的类对象来完成计数任务
**/
class f_mod {
private:
    int mod; // 记录整除的整数
public:
    f_mod(int x = 1) : mod(x) {}
    bool operator()(int x) { return x % mod == 0; }
};
count3 = count_if(vint.begin(), vint.end(), f_mod(3));
count13 = count_if(vint.begin(), vint.end(), f_mod(13));
cout << "count3: " << count3 << ", count13: " << count13 << endl;
```

**使用 Lambda 实现**：

```cpp
int count3 = 0;
int count13 = 0;
// Lambda 版实现 1
count3 = count_if(vint.begin(), vint.end(), [](int x) { return x % 3 == 0; });
count13 = count_if(vint.begin(), vint.end(), [](int x) { return x % 13 == 0; });
cout << "count3: " << count3 << ", count13: " << count13 << endl;
```

#### 为何使用 Lambda

您可能会问，除了那些表达式狂热爱好者，谁还会使用 Lambda 呢？下面从 4 个方面探讨这个问题：距离、简洁、效率、功能。

从距离的角度：很多程序员认为，让定义位于使用的地方附近很有用。这样就无需翻阅多页的源代码，以了解函数调用 count_if() 中的第三个参数了。另外，如果需要修改代码，涉及的内容都将在附近。从这个角度看，Lambda 是理想的选择，因为其定义可能离使用它的地方很远。而函数符是个不错的选择，因为刻在函数内部定义类，因此定义离使用地点也可以很近。

从简洁的角度：函数符代码比函数和 Lambda 代码更频繁，而函数和 Lambda 的简洁程度相当。有一个例外是，需要使用同一个 lambda 两次。但也可以通过给 lambda 指定一个名称，并使用该名称两次：

```cpp
auto mod3 = [](int x) { return x % 3 == 0; };
count1 = count_if(vint1.begin(), vint1.end(), mod3);
count2 = count_if(vint2.begin(), vint2.end(), mod3);
```

甚至还可以像使用常规函数那样使用有名称的 Lambda:

```cpp
bool r = mod3(x);
```

从效率的角度：这三种方法的相对效率取决于编译器内联哪些东西。
- 函数指针方法阻止了内联，因为编译器传统上不会内联其地址被获取的函数，因为函数地址的概念意味着非内联函数。
- 函数符和 Lambda 通常不会阻止内联。

从功能的角度：Lambda 还有一些额外的功能，即可以访问作用域内的变量。

利用这一点，我们还可以用 for_each 来实现该计算功能：

```cpp
count3 = 0;
count13 = 0;
// Lambda 版实现 2
for_each(vint.begin(), vint.end(), [&](int x) { count3 += (x % 3 == 0); count13 += (x % 13 == 0); });
cout << "count3: " << count3 << ", count13: " << count13 << endl;
```

### 包装器

C++提供了多个包装器(wrapper)，也叫适配器(adapter)。
包装器：它是一个类模板，‌能够封装函数指针、‌仿函数类、‌lambda函数等可调用对象，‌使得这些对象能够以统一的方式被调用、‌传递参数和获取返回值。‌
通过使用包装器，‌可以解决不同类型的可调用对象在使用上的不便，‌如函数指针的类型声明复杂、‌仿函数的类型不统一、‌lambda表达式在语法层面没有类型等问题。‌

C++11 提供了模板 bind、men_fn、reference_wrapper 以及包装器 function 模板。其中 bind 允许将某个函数或函数对象绑定到一些具体的参数上；模板 mem_fn 让您能够将成员函数作为常规函数进行传递；模板 reference_wrapper 让您能够创建行为像引用但可被复制的对象；而包装器 function 让您能够以统一的方式处理多种类似于函数的形式。

下面将详细介绍包装器 function。

#### 模板的低效性

请看下面的代码行：

```cpp
answer = ef(q);
```

ef 可以是函数名、函数指针、函数对象、有名称的 Lambda 表达式。所有这些都是可调用的类型。鉴于可调用类型如此丰富，这可能导致模板效率的低效。

为明白这一点，请看一个简单的示例：

```cpp
template<typename T, typename F>
T use_f(T t, F f) {
    static int count = 0;
    count++;
    std::cout << "use_f count = " << count
              << ", &count = " << &count << " ";
    return f(t);
}

double f1(double x) { return 2.0 * x; }
double f2(double x) { return 1.0 + x; }

class F1 {
private:
    double d;
public:
    F1(double x = 1.0) : d(x) {}
    double operator()(double x) { return x * d; }
};

class F2 {
private:
    double d;
public:
    F2(double x = 1.0): d(x) {}
    double operator()(double x) { return x + d; }
};

int main() {
    using namespace std;
    double y = 1.2;
    cout << "Function pointer f1: " << use_f(y, f1) << endl;
    cout << "Function pointer f2: " << use_f(y, f2) << endl;
    cout << "Function object  F1: " << use_f(y, F1(8.8)) << endl;
    cout << "Function object  F2: " << use_f(y, F2(8.8)) << endl;
    cout << "Lambda expression 1: " << use_f(y, [](double x) { return x * x; }) << endl;
    cout << "Lambda expression 2: " << use_f(y, [](double x) { return x / 0.5; }) << endl;
    return 0;
}
```

在每次调用模板 use_f() 时，模板参数 T 都被设置为类型 double。而模板参数 F 在每次调用时，F 都接受一个 double 值，并返回一个 double 值，因此在六次调用 use_f() 中，好像 F 的类型都相同，这样的话应该只会实例化模板一次。

但正如程序的输出表明的，这种想法太天真了：

```cpp
// 输出
Function pointer f1: use_f count = 1, &count = 0x4070d0 2.4
Function pointer f2: use_f count = 2, &count = 0x4070d0 2.2
Function object  F1: use_f count = 1, &count = 0x4070b0 10.56
Function object  F2: use_f count = 1, &count = 0x4070c0 10
Lambda expression 1: use_f count = 1, &count = 0x40b034 1.44
Lambda expression 2: use_f count = 1, &count = 0x40b038 2.4
```

在模板函数 use_f() 中有一个静态成员 count，可以根据它的地址判断模板被实例化了多少次，一共有 5 个不同的地址，这表明模板 use_f() 有 5 个不同的实例化。

我们期望的是模板实例化一次，而实际上模板被实例化了五次，这就是我们说的低效。下面我们来看看为什么模板会被实例化五次。为了解其中的原因，我们需要考虑编译器如何判断模板数 F 的类型。

首先，`use_f(y, f1);`和`use_f(y, f2);`。f1 和 f2 都是函数名，它们接受一个 double 参数并返回一个 double 值。函数名是指针，因此在这两个调用中，F 的类型为`double (*)(double)`，即一个指向函数的指针，该函数接受一个 double 的参数，并返回一个 double 值。

其次，`use_f(y, F1(8.8));`和`use_f(y, F2(8.8));`。它们的第二个参数为类对象，F 的类型分别为 F1 和 F2，因此将为这些 F 值实例化 use_f() 模板两次。

最后，最后两个 Lambda 调用将 F 的类型设置为编译器为 Lambda 表达式使用的类型。

#### 修复问题 —— function 包装器

包装器 function 能够让您重写上述程序，以实现让其只使用 use_f() 的一个实例而不是五个。注意上述程序中的函数指针、类对象、Lambda 都有一个相同的地方，即它们都接受一个 double 参数并返回一个 double 值。也就是说，它们的调用特征标相同 —— `double(double)`。

> 调用特征标是由返回类型以及括号括起来的参数类型列表定义的。

模板 function 在头文件`functional`中声明，它从调用特征标的角度定义了一个对象，可用于包装调用特征标相同的函数指针、函数对象或 Lambda。例如，`function<int(char, double)> ficd;`声明创建了一个名为 ficd 的 function 对象，即它接受一个 char 参数和一个 double 参数，并返回一个 int 参数。
这样，任何接受一个 char 参数和一个 double 参数，并返回一个 int 值的任何函数指针、类对象、Lambda 都可以赋值给它

利用 function，我们可以将上面程序中的 use_f 实例化一次：`use_f(double, function<double(double)>)`：

**Method 1. 将实参转换为 function<double(double)> 类型**

```cpp
function<double(double)> fdd[6] = { f1, f2, F1(8.8), F2(8.8),
                                    [](double x) { return x * x; },
                                    [](double x) { return x / 0.5;} };
cout << "Function pointer f1: " << use_f(y, fdd[0]) << endl;
cout << "Function pointer f2: " << use_f(y, fdd[1]) << endl;
cout << "Function object  F1: " << use_f(y, fdd[2]) << endl;
cout << "Function object  F2: " << use_f(y, fdd[3]) << endl;
cout << "Lambda expression 1: " << use_f(y, fdd[4]) << endl;
cout << "Lambda expression 2: " << use_f(y, fdd[5]) << endl;
```

```cpp
// 输出
Function pointer f1: use_f count = 1, &count = 0x4080e0 2.4
Function pointer f2: use_f count = 2, &count = 0x4080e0 2.2
Function object  F1: use_f count = 3, &count = 0x4080e0 10.56
Function object  F2: use_f count = 4, &count = 0x4080e0 10
Lambda expression 1: use_f count = 5, &count = 0x4080e0 1.44
Lambda expression 2: use_f count = 6, &count = 0x4080e0 2.4
```

当然，也可以不用声明 6 个`function<double(double)>`对象，只使用临时`function<double(double)>对象就可以完成：

```cpp
cout << "Function pointer f1: " << use_f(y, function<double(double)>(f1)) << endl;
```

如果觉得重复写 6 次`function<double(double>)`太麻烦，可以利用 typedef 来简化：

```cpp
typedef function<double(double)> fdd;
cout << "Function object  F2: " << use_f(y, fdd(F2(8.8))) << endl;
```

**Method 2. 修改模板的形参类型声明，让形参 f 的类型与实参匹配**

```cpp
template <typename T>
T use_f(T t, function<T(T)> f) {
    // ...
}
```

这样，函数调用将如下：

```cpp
cout << "Function pointer f1: " << use_f<double>(y, f1) << endl;
cout << "Function object F1: " << use_f<double>(y, F1(8.8)) << endl;
cout << "Lambda expression 1: " << use_f<double>(y, [](double x) { return x * x; }) << endl;
```

因为参数 f1 本身的类型并不是`function<double(double)>`，因此在 use_f() 后面使用了`<double>`来指出所需的具体化。这样，T 被设置为 double，而`function<T(T)>`变成了`function<double(double)>`。
