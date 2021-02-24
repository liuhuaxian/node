# State 状态模式

## 动机(Motivation)

+ 对象状态如果改变，其行为也会随之而发生变化，比如文档处于只读状态，其支持的行为和读写状态支持的行为就可能完全不同。
+ 如何在运行时根据对象的状态来透明地改变对象的行为？


## 模式定义

允许一个对象在其内部状态改变时改变它的行为。从而使对象看起来似乎修改了其行为。
																					——《设计模式》GoF

## 结构

![微信截图_20200827143240](picture\微信截图_20200827143240.png)

## 要点总结

+ State模式将所有与一个特定状态相关的行为都放入一个State的子对象中，在对象状态切换时，切换相应的对象；
  但同时维持State的接口，这样实现了具体操作与状态转换之间的解耦。
+ 转换是原子性的
+ 与Strategy模式类似

## 示例

### 不好的设计模式

`state1.cpp`

```c++
enum NetworkState
{
    Network_Open,
    Network_Close,
    Network_Connect,
};

class NetworkProcessor{
    
    NetworkState state;

public:
    
    void Operation1(){
        if (state == Network_Open){

            //**********
            state = Network_Close;
        }
        else if (state == Network_Close){

            //..........
            state = Network_Connect;
        }
        else if (state == Network_Connect){

            //$$$$$$$$$$
            state = Network_Open;
        }
    }

    public void Operation2(){

        if (state == Network_Open){
            
            //**********
            state = Network_Connect;
        }
        else if (state == Network_Close){

            //.....
            state = Network_Open;
        }
        else if (state == Network_Connect){

            //$$$$$$$$$$
            state = Network_Close;
        }
    
    }

    public void Operation3(){

    }
};
```

### 好的设计模式

`state2.cpp`

```c++
class NetworkState{

public:
    NetworkState* pNext;
    virtual void Operation1()=0;
    virtual void Operation2()=0;
    virtual void Operation3()=0;

    virtual ~NetworkState(){}
};


class OpenState :public NetworkState{
   
    static NetworkState* m_instance;
public:
    static NetworkState* getInstance(){
        if (m_instance == nullptr) {
            m_instance = new OpenState(); //通过多态指针动态的识别当前的状态。
        }
        return m_instance;
    }

    void Operation1(){
        
        //**********
        pNext = CloseState::getInstance();
    }
    
    void Operation2(){
        
        //..........
        pNext = ConnectState::getInstance(); //指定open成功后的下一个状态为connect状态。
    }
    
    void Operation3(){
        
        //$$$$$$$$$$
        pNext = OpenState::getInstance();
    }
    
    
};

class CloseState:public NetworkState{ }
//...


class NetworkProcessor{
    
    NetworkState* pState;
    
public:
    
    NetworkProcessor(NetworkState* pState){
        
        this->pState = pState;
    }
    
    void Operation1(){
        //...
        pState->Operation1();
        pState = pState->pNext;//多态指针动态的指定下一个状态。
        //...
    }
    
    void Operation2(){
        //...
        pState->Operation2();
        pState = pState->pNext;
        //...
    }
    
    void Operation3(){
        //...
        pState->Operation3();
        pState = pState->pNext;
        //...
    }

};
```

