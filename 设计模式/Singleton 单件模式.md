# Singleton 单件模式

## 动机

- 在软件系统中，经常有这样的一些特殊的类，必须保证他们在系统中只存在一个实例，才能保证他们的逻辑正确性，以及良好的效率。

## 模式定义

保证一个类仅有一个实例，并提供一个该实例的全局访问点。

​																						-----《设计模式》

## 结构

![微信截图_20200825154733](picture\微信截图_20200825154733.png)

## 要点总结

- Singleton模式中的实例构造器可以设置为protected以允许子类派生。
- Singleton模式一般不支持拷贝构造函数和Clone接口，因为这有可能导致多个对象实例，与Singleton模式的初衷违背。
- 如何实现多线程环境下安全的Singleton？注意对双检查锁的正确实现。

## 示例代码

`Singleton.cpp`

```c++
class Singleton{
private:
    Singleton();
    Singleton(const Singleton& other);
public:
    static Singleton* getInstance();
    static Singleton* m_instance;
};

Singleton* Singleton::m_instance=nullptr;

//线程非安全版本
Singleton* Singleton::getInstance() {
    if (m_instance == nullptr) {
        m_instance = new Singleton();
    }
    return m_instance;
}

//线程安全版本，但锁的代价过高
Singleton* Singleton::getInstance() {
    Lock lock; //采用双检查锁机制
    if (m_instance == nullptr) {
        m_instance = new Singleton();
    }
    return m_instance;
}

//双检查锁，但由于内存读写reorder不安全。
/*reorder指的是一个对象的产生顺序理想的为1：分配空间 2：调用其构造器 3：将分配的地址返回给对象。
但实际上可能不是这样的情况（由于编译器的优化），先进行 1->2->3。此时如果这个现象出现在38行的时候
当该线程在1->2阶段的时候时间片到了，此时m_instance不为nullptr，但此时其并没由初始化完成。此时当另一个线程使用对象的时候，认为其以及构造完成（m_instance不为nullptr），使用了该对象，则会出现异想不到的结果。
*/
Singleton* Singleton::getInstance() {
    
    if(m_instance==nullptr){ //避免高并发的情况进行访问操作也加上锁，导致大量线程阻塞等待。
        Lock lock; 
        if (m_instance == nullptr) {
            m_instance = new Singleton();
        }
    }
    return m_instance;
}


//C++ 11版本之后的跨平台实现 (volatile)
std::atomic<Singleton*> Singleton::m_instance;
std::mutex Singleton::m_mutex;

Singleton* Singleton::getInstance() {
    Singleton* tmp = m_instance.load(std::memory_order_relaxed);
    std::atomic_thread_fence(std::memory_order_acquire);//获取内存fence
    if (tmp == nullptr) {
        std::lock_guard<std::mutex> lock(m_mutex);
        tmp = m_instance.load(std::memory_order_relaxed);
        if (tmp == nullptr) {
            tmp = new Singleton;
            std::atomic_thread_fence(std::memory_order_release);//释放内存fence
            m_instance.store(tmp, std::memory_order_relaxed);
        }
    }
    return tmp;
}
```

