

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









//双检查锁，但由于内存读写reorder不安全 (流水线技术读-改-写)。
Singleton* Singleton::getInstance() {
    
    if(m_instance==nullptr){
		//当一个线程完成读-改操作时，时间片到，此时还没有上锁，另一个线程就可以成功进入创建对象。
		//当再次调用此线程时，完成写的操作，再次创建了对象。
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








