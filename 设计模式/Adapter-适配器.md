# Adapter 适配器

## 动机(Motivation)

+ 由于应用环境的变化，常常需要将”一些现存的对象“放在新的环境中应用，但是新环境要求的接口是这些现存对象所不满足。
+ 如何应对这些”迁移的变化“？

## 模式定义

将一个类的接口转换成客户希望的另一个接口。Adapter模式使得原本由于接口不兼容而不能一起工作的那些类可以一起工作。
——《设计模式》GoF

## 结构

![微信截图_20200827131144](picture\微信截图_20200827131144.png)

## 要点总结

- Adapter模式主要应用于"希望复用一些现存的类，但接口又与复用环境要求不一致的情况"，在遗留代码复用、类库迁移等方面非常有用。
- GoF 23定义了两种Adapter模式的实现结构：对象适配器和类适配器。但类适配器采用"多继承"的实现方式，一般不推荐使用。对象适配器采用对象组合的方式，更加符合松耦合精神。
- Adapter模式可以实现的非常灵巧，不必局限于该形式。

## 示例代码

`Adapter.cpp`

```c++
//目标接口（新接口）
class ITarget{
public:
    virtual void process()=0;
};

//遗留接口（老接口）
class IAdaptee{
public:
    virtual void foo(int data)=0;
    virtual int bar()=0;
};

//遗留类型,有复用价值的接口。
class OldClass: public IAdaptee{
    //....
};

//对象适配器
class Adapter: public ITarget{ //继承
protected:
    IAdaptee* pAdaptee;//组合有复用价值的接口
    
public:
    
    Adapter(IAdaptee* pAdaptee){
        this->pAdaptee=pAdaptee;
    }
    
    virtual void process(){
        int data=pAdaptee->bar();
        pAdaptee->foo(data);
        
    } 
};


//类适配器
class Adapter: public ITarget,
               protected OldClass{ //多继承
               
               
}


int main(){
    IAdaptee* pAdaptee=new OldClass();
    
    
    ITarget* pTarget=new Adapter(pAdaptee);
    pTarget->process();
    
    
}


class stack{
    deqeue container;
    
};

class queue{
    deqeue container;
    
};
```

