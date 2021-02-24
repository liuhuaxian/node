# C++四种类型转换总结     

C风格的强制类型转换很简单，均用 Type b = (Type)a 形式转换。C++风格的类型转换提供了4种类型转换操作符来应对不同场合的应用，如下表：

| 转换类型操作符   | 作用                                                         |
| ---------------- | ------------------------------------------------------------ |
| const_cast       | 去掉类型的const或volatile属性                                |
| static_cast      | 无条件转换，静态类型转换                                     |
| dynamic_cast     | 有条件转换，动态类型转换，运行时检查类型安全（转换失败返回NULL） |
| reinterpret_cast | 仅重新解释类型，但没有进行二进制的转换                       |

**1、const_cast**

去掉类型的const或volatile属性

```
int main() {

    struct T {
        int i;
    };

    const T a;
    //a.i = 10;  //直接修改const类型，编译错误
    T &b = const_cast<T&>(a);
    b.i = 10;

    return 0;
}
```

**2、static_cast**

类似C风格的强制转换，进行无条件转换，静态类型转换：

1）基类和子类之间的转换：其中子类指针转换为父类指针是安全的，但父类指针转换为子类指针是不安全的（基类和子类之间的动态类型转换建议用dynamic_cast）。

2）基本数据类型转换，enum，struct，int，char，float等。static_cast不能进行无关类型（如非基类和子类）指针之间的转换。

3）把任何类型的表达式转换成void类型。

4）static_cast不能去掉类型的const、volatile属性（用const_cast）。

```
int main() {

    int n = 6;
    double d = static_cast<double>(n);     //基本类型转换
    int *pn = &n;
    double *d = static_cast<double*>(&n);  //无关类型转换，编译错误
    void *p = static_cast<void*>(pn);

    return 0;
}
```

**3、dynamic_cast**

有条件转换，动态类型转换，运行时检查类型安全（转换失败返回NULL）：

1）安全的基类和子类之间的转换。

2）必须有虚函数。

3）相同基类不同子类之间的交叉转换，但结果返回NULL。

```
class Base {
public:
    int _i;
    virtual void foo() {}; //基类必须有虚函数。保持多态特性才能使用dynamic_cast
};

class Sub : public Base {
public:
    char *_name[100];
    void Bar() {};
};

int main() {

    Base* pb = new Sub();
    Sub* ps1 = static_cast<Sub*>(pb);  //子类->父类，静态类型转换，正确但不推荐
    Sub* ps2 = dynamic_cast<Sub*>(pb); //子类->父类，动态类型转换，正确

    Base* pb2 = new Base();
    Sub* ps21 = static_cast<Sub*>(pb2); //父类->子类，静态类型转换，危险！访问子类_name成员越界
    Sub* ps22 = dynamic_cast<Sub*>(pb2);//父类->子类，动态类型转换，安全，但结果为NULL

    return 0;
}
```

**4、reinterpret_cast**

仅重新解释类型，但没有进行二进制的转换：

1）转换的类型必须是一个指针，应用、算术类型、函数指针或者成员指针。

2）在比特级别上进行转换，可以把一个指针转换成一个整数，也可以把一个整数转换成一个指针（先把一个指针转换成一个整数，在把该整数转换成原类型的指针，还可以得到原先的指针值）。但不能将非32bit的实例转成指针。
3） 最普通的用途就是在函数指针类型之间进行转换。
4） 很难保证移植性。

```
int doSomething() { 
    return 0; 
};

int main() {
    typedef void(*FuncPtr)(); //FuncPtr is 一个指向函数的指针，该函数没有参数，返回值类型为 void
    FuncPtr funcPtrArray[10]; //10个FuncPtrs指针的数组 让我们假设你希望（因为某些莫名其妙的原因）把一个指向下面函数的指针存入funcPtrArray数组：

    funcPtrArray[0] = &doSomething;// 编译错误！类型不匹配，reinterpret_cast可以让编译器以你的方法去看待它们：funcPtrArray
    funcPtrArray[0] = reinterpret_cast<FuncPtr>(&doSomething); //不同函数指针类型之间进行转换

    return 0;
}
```

**总结**

去const属性用const_cast

基本类型转换用static_cast

多态类之间的类型转换用dynamic_cast

不同类型的指针类型转换用reinterpret_cast

转载https://www.cnblogs.com/evenleee/p/10382335.html