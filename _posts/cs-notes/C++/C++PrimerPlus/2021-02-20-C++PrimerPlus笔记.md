---
title: 《C++PrimerPlus》读书笔记
date: 2015-03-12 08:55:00 +0800
categories: [CS, C/C++]
tags: [C/C++]
---

《C++PrimerPlus》读书笔记


### 函数模板
函数模板是通用的函数描述，使用泛型来定义函数，其中的泛型可用具体的类型替换。通过将类型作为参数传递给模板，可使编译器生成该类型的函数。代码见附录`function_template.cpp`

**显式具体化:** 为特定类型提供具体化的模板定义，当编译器找到与函数调用匹配的具体化定义时，将使用该定义，而不再寻找模板。
- 对于给定的函数名，可以有非模板函数、模板函数和显式具体化模板函数以及他们的重载版本。
- 显式具体化的原型和定义应以`template<>`开头，并通过名称来指出类型。
- 具体化优先于常规模板，而非模板函数优先于具体化和常规模板。

**关键字decltype（C++11）**         
有时我们希望从表达式的类型推断出要定义的变量类型，但是不想用该表达式的值初始化变量。为了满足这一需求，C++11新标准引入了`decltype`类型说明符，它的作用是选择并返回操作数的数据类型，在此过程中，编译器分析表达式并得到它的类型，却不实际计算表达式的值。
```c++
template<class T1, class T2>
void printplus(T1 a, T2 b) {
    decltype(a+b) c = a + b;        // 如果这里不用decltype，无法判断a+b的结果是T1类型还是T2类型或者其他类型
    cout << c;
}
```

### 友元friend
在C++中非类成员函数是不能直接访问私有成员及私有成员函数的，但有时候我们又需要某些函数或者类可以打破这个限制，可以访问到，这就是C++友元机制。友元有三种：
- 友元函数
- 友元类
- 友元成员函数

代码示例见附录`friend.cpp`


### 异常机制
C++异常是对程序运行过程中发生的异常情况的一种响应，异常提供了将控制权从程序的一部分传递到另一部分的途径。在C++中，主要用`try-catch`捕获异常。

代码示例见附录`abort.cpp`

C++11中新增了一个关键字`noexcept`指出函数不会引发异常：
```c++
double marm() noexcept;     //marm() doesn't throw an exception.
```
当使用这个关键字时，等于是程序员向编译器做出了承诺，放心吧，这个函数不会引发异常。


### 智能指针
比较早的智能指针是`auto_ptr`，但现在已经不推荐使用，现在推荐使用的智能指针是`unique_ptr`、`shared_ptr`、`weak_ptr`。那这三种智能指针该如何使用呢？

如果程序要使用多个指向同一个对象的指针，应选择`shared_ptr`。如果程序不需要多个指向同一个对象的指针，则可使用`unique_ptr`。`weak_ptr`较为特殊，一般与`shared_ptr`配合使用，它可以指向`shared_ptr`所指向的对象，但却不增加对象的引用计数，这样就有可能出现`weak_ptr`所指向的对象实际上已经被释放了的情况。

代码示例见附录`cpp11.cpp`

### C++11
前面已经提到一些C++11的内容，这里再继续谈一些。当然，这里列出的不是全部，只选取了其中一部分。

1. 增加了新类型`long long`、`unsigned long long`、`char16_t`、`char32_t`。

2. 增加了空指针`nullptr`，推荐使用`nullptr`而不是0提供了更高类型的安全。

3. 新的基于范围的`for`循环。

4. 新增智能指针`unique_ptr`、`shared_ptr`、`weak_ptr`。

5. 右值引用`&&`，移动语义（move semantics）。

6. Lambda表达式。

7. 并行编程。

代码示例见附录`cpp11.cpp`

### Boost
开源库，里面有很多库，比如常用的日志库、线程库等。



---
### 附录
#### function_template.cpp
```c++
// 函数模板示例代码

#include<iostream>
#include<string>
using namespace std;

struct City {
    string name;
    int population;
};

template<class T>
void Swap(T &a, T &b);

template<> void Swap<City>(City &a, City &b);

template<class T1, class T2>
void printplus(T1 a, T2 b);

int main() {
    int a = 10;
    decltype(a) b = 20;
    Swap(a, b);
    cout << a << b;

    double da = 10.1;
    double db = 100.1;
    Swap(da, db);
    cout << da << db << endl;;

    City ca = {"beijing", 2100};
    City cb = {"shanghai", 2400};
    Swap(ca, cb);    
    cout << ca.name << ":" << ca.population << endl;
    cout << cb.name << ":" << cb.population << endl;

    printplus(a, da);    

}

// 常规模板
template<class T>
void Swap(T &a, T &b) {
    T tmp;
    tmp = a;
    a = b;
    b = tmp;
}

// 具体化模板
template<> void Swap<City>(City &a, City &b) {
    int tmp = a.population;
    a.population = b.population;
    b.population = tmp;
}

template<class T1, class T2>
void printplus(T1 a, T2 b) {
    decltype(a+b) c = a + b;        // 如果这里不用decltype，无法判断a+b的结果是T1类型还是T2类型或者其他类型
    cout << c;
}
```

#### friend.cpp
```c++
// 友元及运算符重载 示例程序

#include<iostream>
using namespace std;

class T {
public:
    T(int n):count(n){}
    T operator+(const T & t) {
        this->count = this->count + t.count;
        return *this;
    }
    friend std::ostream & operator<<(std::ostream & os, const T & t);
private:
    int count;
};

std::ostream & operator<<(std::ostream & os, const T & t) {
    os << t.count;
}

int main() {
    T t1(10);
    T t2(1);
    cout << (t1 + t2) << endl;
}
```

#### cpp11.cpp
```c++
// c++ 智能指针
#include<iostream>
#include<string>
#include<memory>
#include<vector>
#include<cassert>

using namespace std;

void cpp11();
void smart_pointer();

class Useless {
public:
    Useless();
    // explicit Useless(int k);
    Useless(int k, char ch);
    Useless(const Useless& u);
    Useless(Useless&& u);   // 移动构造函数
    ~Useless();
    void show_data() const;
    Useless operator+(const Useless& u) const;
private:
    int n;
    char* pc;
    static int ct;
    void show_object() const;

};

int Useless::ct = 0;
Useless::Useless() {
    ++ct;
    n = 0;
    pc = nullptr;
    cout << "default constructor called, number of objects: " << ct << endl;
}

Useless::Useless(int k, char ch):n(k) {
    ++ct;
    cout << "init constructor called, number of object: " << ct << endl;
    pc = new char[n];
    show_object();
}

Useless::Useless(const Useless& u):n(u.n) {
    ++ct;
    cout << "copy constructor called, number of object: " << ct << endl;
    pc = new char[n];
    for (int i = 0; i < n; ++i) 
        pc[i] = u.pc[i];
    show_object();
}

Useless::Useless(Useless&& u):n(u.n) {
    ++ct;
    cout << "move constructor called, number of object: " << ct << endl;
    pc = u.pc;
    u.pc = nullptr;
    u.n = 0;
    show_object();
}

Useless::~Useless() {
    cout << "destructor called; objects left: " << --ct << endl;
    show_object();
    delete [] pc;
}

void Useless::show_object() const {
    cout << "n: " << n << " , data addr: " <<  (void *)pc << endl;
}

void Useless::show_data() const {
    cout << "data: ";
    for (int i = 0; i < n; ++i) {
        cout << pc[i] << " ";
    }
    cout << endl;
}

Useless Useless::operator+(const Useless& u) const {
    assert(u.n == n);
    Useless t = Useless(n, '0');
    for (int i = 0; i < n; ++i) {
        t.pc[i] = pc[i] + u.pc[i];
    }

    return t;
}

int main() {
    smart_pointer();
    cpp11();
    Useless one(10, 1);
    Useless two(one);
    two.show_data();
    Useless three(10, 64);
    Useless four (one + three);
    four.show_data();

    return 0;
}

void smart_pointer() {
    unique_ptr<string> p1(new string("auto"));
    cout << *p1 << endl;
    unique_ptr<string> p2;
    p2 = std::move(p1); // 这里必须加move，否则编译错误，相比auto_ptr，增加了安全性
    cout << *p2 << endl;    

    // shared_ptr采用引用计数的方式管理所指向的对象
    shared_ptr<string> p3 = make_shared<string>("shared pointer.");
    cout << *p3 << p3.use_count() << endl;
    {
        auto p4 = p3;
        cout << *p4 << p4.use_count() << endl;
    }
    cout << *p3 << p3.use_count() << endl;

    weak_ptr<string> p5(p3);
    auto p6 = p5.lock();
    cout << *p6 << p5.use_count() << endl;
}

void cpp11() {
    cout << "long long:" << sizeof(long long) << endl;
    cout << "char16_t: " << sizeof(char16_t) << endl;
    cout << "char32_t: " << sizeof(char32_t) << endl;

    std::vector<int> v1(6);
    for (auto &x : v1) {
        x = std::rand();
    }

    cout << "v1: ";
    for (auto i : v1) {
        cout << i << " ";
    }
    cout << endl;

}
```

#### abort.cpp
```c++
// 异常处理
#include<iostream>
using namespace std;

double hmean(double a, double b);

int main() {
    double x, y, z;
    cout << "enter two numbers: ";
    while (cin >> x >> y) {
        try {
            z = hmean(x, y);
        }
        catch (const char* s)
        {
            cout << s << endl;
            cout << "Enter a new pair of numbers:";
            continue;
        }
        cout << "result is :" << z << endl;
    }

    return 0;
}

double hmean(double a, double b) {
    if (a == -b) {
        //抛出一个异常，这里是字符串，也可以是一个对象，相应的catch里捕获的也是一个对象
        throw "bad hmean() arguments: a = -b not allowed."; 
    }
    return 2.0 * a * b / (a + b);

}
```